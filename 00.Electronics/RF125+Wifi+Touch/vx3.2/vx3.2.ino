/*  RDM630/6300 + WIFI+ Touch
 *  (c) An Minh Dao 2018 
 */

 #define DEBUG_BASIC
 #define DEBUG_ADVANCE

#include "config.h"

/******** Global State  ********/
// Create an ESP32 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS);

/******** Initialize Feeds ********/
//PUBLISH
Adafruit_MQTT_Publish ID = Adafruit_MQTT_Publish(&mqtt,ID_FEED,MQTT_QOS_1);
Adafruit_MQTT_Publish facility = Adafruit_MQTT_Publish(&mqtt,FACILITY_FEED,MQTT_QOS_1);
//SUBCRIBE
Adafruit_MQTT_Subscribe command = Adafruit_MQTT_Subscribe(&mqtt,COMMAND_FEED,MQTT_QOS_1);

///////////////////////////TOUCH BUTTON INTERRUPT SETUP//////////////////////////////////////////
void gotTouch() {
  if (roomON==true) { //open the pheripheral box (power the solenoid)
    digitalWrite(SOLENOID,HIGH);
    lastmillis_touch = millis();
  }//end if
}//end gotTouch
//////////////////////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR catchID() { //CAUTION: must change Watchdog Interrupt Timeout configurations to 1000ms before proceed!!
    detachInterrupt(18);
    uint8_t ssvalue;
    uint8_t count=0;
    
    while (1) {
      ssvalue = Serial2.read(); // read
      if (ssvalue==2) {
        count=0;
        buffer_index = 0;
        buffer[buffer_index++] = ssvalue; // everything is alright => copy first letter into buffer
        while (1) {
          ssvalue = Serial2.read(); // read
          buffer[buffer_index++] = ssvalue; // everything is alright => copy current value to buffer
          if (ssvalue==3) {
            if (buffer_index == BUFFER_SIZE) {
             GetID();
             gotID=true;
             Serial2.end();
             return;
           }//end if
           else {
            #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
            Serial.println(F("Something is wrong...starting again..."));
            #endif
            attachInterrupt(18, catchID, FALLING);
            return;
           }//end else
          }//end ssvalue==3 (end of signal)
          if (buffer_index > BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
            #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
            Serial.println(F("Error: Buffer overflow detected!"));
            #endif
            attachInterrupt(18, catchID, FALLING);
            return;
          }//end if
          if (count++>13){attachInterrupt(18, catchID, FALLING); return;} //something is wrong so no ending signal (3) is detected (14 signal, first one have been count already, so if it bigger than 13, that means it have more than 14 elements)
        }//end while
      }//end ssvalue==2 (begin signal)

      if (count++==20) {attachInterrupt(18, catchID, FALLING); return;} //no data was read
  }//end while
}//end interrupt

void setup() {
 WiFi.mode(WIFI_STA);
 Serial.begin(115200);
 Serial2.begin(9600); //default baudrate for RDM630/6300
  
 Wifi_begin(); // We start by connecting to a WiFi network
 mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN); //Set up last will

 mqtt.subscribe(&command); // Set up MQTT subscriptions.
 
 pinMode(18, INPUT);
 attachInterrupt(18, catchID, FALLING);
 touchAttachInterrupt(T0, gotTouch, THRESHOLD);

 #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
 Serial.println(F("Initialize Done."));
 #endif
 #ifdef DEBUG_ADVANCE
 Serial.println(F("ADVANCED DEBUG Mode"));
 #endif


 pinMode(MAIN_RELAY, OUTPUT);
 pinMode(SOLENOID, OUTPUT);
 digitalWrite(MAIN_RELAY,LOW);
 digitalWrite(SOLENOID,LOW);
 lastmillis = millis();

 MQTT_connect();
 #if not defined (DEBUG_BASIC) || not defined (DEBUG_ADVANCE)
 facility.publish("online");
 #endif
 #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
 if (! facility.publish("online")) {Serial.println(F("Failed"));} 
 else                              {Serial.println(F("OK!"));}
 #endif
}//end setup

void loop() {
  MQTT_connect();
  
  //PUBLISH:
  if (gotID) {
    gotID=false;
    #if not defined (DEBUG_BASIC) || not defined (DEBUG_ADVANCE)
    ID.publish(strID); //strID is an array
    #endif
    #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
    if (! ID.publish(strID)) {Serial.println(F("Failed!"));}
    else                     {Serial.println(F("Published!"));}
    #endif
    Serial2.begin(9600);
    attachInterrupt(18, catchID, FALLING);
  }//end if gotID


  //SUBCRIBE:
  // this is our 'wait for incoming subscription packets' busy subloop
   Adafruit_MQTT_Subscribe *subscription;                  
     while ((subscription = mqtt.readSubscription(1000))) {      //wait for signal
        if (subscription == &command) {                         // if something new is detected on this topic
           Execute_Command();
           }//end if
  }//end while

  if ((millis()-lastmillis_touch)>1000) {digitalWrite(SOLENOID,LOW);} //take advantages of the waiting time of the subcribe loop

  if((! mqtt.ping())&&((millis()-lastmillis)>180000)) { // ping the server to keep the mqtt connection alive
    lastmillis = millis(); //180second
    mqtt.disconnect();
    }//end if
}//end loop
/////////////////////////////////////////////////////////////////////////////////////////////

void Wifi_begin() {
  // Connect to WiFi access point.
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);
  #endif

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
    Serial.print(".");
    #endif
  }
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: ")); Serial.println(WiFi.localIP());
  Serial.println();
  #endif
}//end wifi begin

void MQTT_connect() {// Ensure the connection to the MQTT server is alive (this will make the first connection and automatically reconnect when disconnected).
  
  int8_t ret;
  if (mqtt.connected()) {return;} // Stop if already connected.

  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.print(F("Connecting to MQTT... "));
  #endif
  
  while ((ret = mqtt.connect()) != 0)  {         // connect will return 0 for connected
       #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)                         
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(F("Retrying MQTT connection in 1 seconds..."));
       #endif
       mqtt.disconnect();
       delay(1000);  // wait 5 seconds
  }//end while
  
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.println(F("MQTT Connected!"));
  #endif
}//end MQTT connect

void GetID() {
    uint8_t *msg_data = buffer + 1; //13 byte, 10 byte data, 2 byte checksum, 1 byte tail
    #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
    uint8_t *msg_data_tag = buffer + 3; //11 byte, 8 byte data, 2 byte checksum, 1 byte tail
    #endif
    uint8_t *msg_checksum = buffer + 11; // 3 byte, 2 byte checksum, 1 byte tail
    volatile long checksum = 0;
    for (int i = 0; i < DATA_SIZE; i+= CHECKSUM_SIZE) {
      volatile long val = hexstr_to_value(msg_data + i, CHECKSUM_SIZE);
      checksum ^= val;
    }//end for
    char good = (checksum == hexstr_to_value(msg_checksum, CHECKSUM_SIZE))? 1:0; //compare calculated checksum to retrieved checksum

    if (good==1) {//checksum return good value
      
      for (uint8_t i = 0; i < DATA_SIZE;i++) {
        strID[i] = msg_data[i];
      }//end for
      strID[DATA_SIZE]='\0';

      #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
      Serial.println();
      Serial.println(F("--------"));
      Serial.println(F("Checksum PASSED "));
      Serial.print(F("Full Identity (HEX): ")); 
      Serial.println((String)strID);
      #endif
      
      #ifdef DEBUG_ADVANCE
      Serial.print(F("Tag only (HEX): "));
      for (int i = 0; i < DATA_TAG; ++i) {
        Serial.print(char(msg_data_tag[i]));
      }//end for
      Serial.println();
      Serial.print(F("Card Version (HEX): "));
      for (int i = 0; i < DATA_VERSION; ++i) {
        Serial.print(char(msg_data[i]));
      }//end for
      Serial.println();

      long tag = hexstr_to_value(msg_data_tag,DATA_TAG);
      Serial.print(F("Decimal Tag: "));
      Serial.println(tag);

      Serial.print(F("Checksum Code (HEX)(matched): "));
      for (int i = 0; i < CHECKSUM_SIZE; ++i) {
        Serial.print(char(msg_checksum[i]));
      }//end for
      Serial.println();
      #endif
    }//end if
  else {//checksum return bad value, do nothing but pop up message
      #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
      Serial.println(F("Checksum FAILED "));
      Serial.print(F("Original Checksum code: ")); 
      for (int i = 0; i < CHECKSUM_SIZE; ++i) {
        Serial.print(char(msg_checksum[i]));
      }//end for
      Serial.println(F("Result recieved: "));
      Serial.print(checksum, HEX);Serial.println();
      Serial.println(F("Please scan your ID card again!"));
      #endif
  }//end else
    #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
    Serial.println(F("--------"));
    #endif
}//end GetID

long hexstr_to_value(unsigned char *str, unsigned int str_length) { // converts a hexadecimal value (encoded as ASCII string) to a numeric value
  //converting an a part of an array into a string (string is an array with null at the end)
  char* copy = (char*)malloc((sizeof(char) * str_length) + 1); 
  memcpy(copy, str, sizeof(char) * str_length);
  copy[str_length] = '\0'; 
  // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
  long value = strtol(copy, NULL, 16);  // strtol converts a null-terminated string to a long value
  free(copy); // clean up 
  return value;
}//end hex string to value

void Execute_Command() {
  String data = (char*)command.lastread;   // Function to analize the string
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.print(F("Get command: ")); Serial.println(data);
  #endif
  if (data=="on") {digitalWrite(MAIN_RELAY,HIGH);roomON=true;} //on
  if (data=="off"){digitalWrite(MAIN_RELAY,LOW);roomON=false;} //off

}//end execute command
