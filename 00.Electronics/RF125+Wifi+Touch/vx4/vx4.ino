/*  RDM630/6300 + WIFI+ Touch
 *  (c) An Minh Dao 2018 
 */

 #define DEBUG_BASIC
 #define DEBUG_ADVANCE

#include "config.h"
#include "EEPROM_Wifi_Access.h"
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

/////////////////////////////// TOUCH BUTTON INTERRUPT ////////////////////////////////////////
void gotTouch() {
  if (roomON==true) { //open the pheripheral box (power the solenoid)
    digitalWrite(SOLENOID,HIGH);
    lastmillis_touch = millis();
  }//end if
}//end gotTouch
///////////////////////////////// RDM6300 INTERRUPT ///////////////////////////////////////////
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

 EEPROM.begin(EEPROM_SIZE);
 gettingEEPROM(); //leave it here for temporary id and password wifi, DO NOT MOVE BELOW WFconnect
  
 WFconnect:
 Wifi_begin(); // We start by connecting to a WiFi network
 ResetID();
 if (signalReset==1) {signalReset=0; goto WFconnect;}

 
 //Wifi_begin(); // We start by connecting to a WiFi network
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


void ResetID() {
  if (signalReset==1) {
    //signalReset=1;
    Serial.println();
    Serial.println(F("ID and Password of currently stored Acess Point seem not working..."));
    Serial.println(F("Log in to another Acess Point?  Y/N"));
    long oldmillis=millis();
    while (Serial.available()==0) {
    if ((millis()-oldmillis)>5000) {
      Serial.println(F("'NO' Request Recieved"));
      Serial.println(F("Trying to reconnect again with the existed information..."));
      break;
    }//end if 5s
   } // end while no signal
    while(Serial.available()>0) {//some signal appeared
    char ch = Serial.read();
    if (ch=='y'||ch=='Y') {
    delay(5);
    Serial.println(F("'YES' Request Recieved"));
    Serial.println(F("Please type in new Wifi ID: (use NO LINE ENDING mode to type)"));
    WLAN_SSID=GetData();
    Serial.println(F("Please type in the corresponding password: (use NO LINE ENDING mode to type)"));
    WLAN_PASS=GetData();
    Serial.println(F("Do you want to save these values in EEPROM?   Y/N"));
    while(Serial.available()==0) {}// do nothing...
    while(Serial.available()>0) {//recieved something
    char ch = Serial.read();
    if (ch=='Y'|ch=='y') {savingEEPROM();Serial.println(F("Wifi ID and Password has been saved"));delay(500);Serial.println(F("Prepare to reconnect..."));}
    else {Serial.println(F("You chose to NOT save these value in EEPROM (will be lost after reset)"));Serial.println(F("Prepare to reconnect..."));}
    delay(500);
    }//end serial available
    Serial.println(F("Reconnecting..."));
    }//end yes
    else {
    Serial.println(F("NO Request Recieved"));
    Serial.println(F("Trying to reconnect again with the existed information..."));
    break;
       }//end no
     }//end while co du lieu tu serial
  }//end signalReset==1
}//end ResetID

String GetData() {
  String data = "";
  while(Serial.available()==0) {}// do nothing...
  while(Serial.available()>0) {//Nhan du lieu
    char ch = Serial.read();
    data = data + ch;
    delay(5); //for stablize
  }//end while nhan du lieu
  Serial.println(F("Recieved: "));
  Serial.println(data);
  return data;
}//end GetData

void gettingEEPROM() {
  Wifi_idlength = EEPROM.read(0);
  Wifi_passlength = EEPROM.read(1);
  for (int i=2;i<(Wifi_idlength+2);i++) {
    WLAN_SSID += (char)EEPROM.read(i);
  }
  for (int k=(Wifi_idlength+2);k<(2+Wifi_idlength+Wifi_passlength);k++) {
    WLAN_PASS += (char)EEPROM.read(k);
  }
}//end gettingEEPROM

void savingEEPROM() {
  EEPROM.put(0,WLAN_SSID.length());
  delay(2); //for stablize
  EEPROM.put(1,WLAN_PASS.length());
  delay(2); //for stablize
  Wifi_idlength = EEPROM.read(0);
  Wifi_passlength = EEPROM.read(1);
  
  char _WLAN_SSID[WLAN_SSID.length()]; //minh dang can char nen bo qua gia tri n+1 cua string (la \0)
  WLAN_SSID.toCharArray(_WLAN_SSID,WLAN_SSID.length()+1);
  char _WLAN_PASS[WLAN_PASS.length()];
  WLAN_PASS.toCharArray(_WLAN_PASS,WLAN_PASS.length()+1);
  
  for (int i=2;i<(Wifi_idlength+2);i++) {
    EEPROM.put(i,_WLAN_SSID[i-2]);
    delay(2); //for stablize
  }
  for (int k=(Wifi_idlength+2);k<(2+Wifi_idlength+Wifi_passlength);k++) {
    EEPROM.put(k,_WLAN_PASS[k-2-Wifi_idlength]);
    delay(2); //for stablize
  }
  EEPROM.commit();
}//end savingEEPROM

void Wifi_begin() {  //HAS BEEN MODIFIED A LOT TO FIT EEPROM MODULE

  char __WLAN_SSID[WLAN_SSID.length()]; //minh dang can char nen bo qua gia tri n+1 cua string (la \0)
  WLAN_SSID.toCharArray(__WLAN_SSID,WLAN_SSID.length()+1);
  char __WLAN_PASS[WLAN_PASS.length()];
  WLAN_PASS.toCharArray(__WLAN_PASS,WLAN_PASS.length()+1);

  
  // Connect to WiFi access point.
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(__WLAN_SSID);
  #endif

  WiFi.begin(__WLAN_SSID, __WLAN_PASS);
  
  char count=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); count++;
    #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
    Serial.print(".");
    #endif
    if (count>7) {count=0; signalReset=1;return;}
  }
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: ")); Serial.println(WiFi.localIP());
  Serial.println();
  #endif
}//end wifi begin
