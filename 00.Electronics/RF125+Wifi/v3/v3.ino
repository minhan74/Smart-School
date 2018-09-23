/*  RDM630/6300 + WIFI
 *  (c) An Minh Dao 2018 
  */
////////////////////////////////////////COMMUNICATION SETUP//////////////////////////////////
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

/******** WiFi Access Point *********/
#define WLAN_SSID       "Home"
#define WLAN_PASS       "minhan74"

/******** MQTT Client Setup **********/

#define SERVER          "m11.cloudmqtt.com"
#define PORT            12180                   // use 22180 for SSL
#define USERNAME        "bmlflxes"
#define PASS            "Mj8LHanZvdkf"
#define CLIENT_ID       "B1/101" 

//#define LWT_TOPIC       "B1/last-will"
//#define LWT_PAYLOAD     "offline"
//#define LWT_RETAIN      1                       //The broker will store the last message as the last known good value
//MQTT_CONN_KEEPALIVE is defined inside the Adafruit_MQTT.h (default 5 minutes) --> need to change to 15 min (900)
//CLEAN_SESSION is defined as TRUE as always clean the session

/******** Global State  ********/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS);

/******** Initialize Feeds ********/
//PUBLISH
Adafruit_MQTT_Publish studentID = Adafruit_MQTT_Publish(&mqtt,"B1/101/ID",MQTT_QOS_1);

//SUBCRIBE
Adafruit_MQTT_Subscribe command = Adafruit_MQTT_Subscribe(&mqtt,"B1/101/command",MQTT_QOS_1);

///////////////////////////RDM6300/6300 125Khz SETUP//////////////////////////////////////////
//#define DEBUG

#define BUFFER_SIZE        14 // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
#define DATA_SIZE          10 // 10byte data (2byte version + 8byte tag)
#define CHECKSUM_SIZE    2 // 2byte checksum

#ifdef DEBUG
#define DATA_VERSION  2 // 2byte version (actual meaning of these two bytes may vary)
#define DATA_TAG      8 // 8byte tag
#endif

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame 
uint8_t buffer_index = 0;
//////////////////////////////////////////////////////////////////////////////////////////////
void IRAM_ATTR catchID() { //CAUTION: must change Watchdog Interrupt Timeout configurations to 1500ms before proceed!!
    detachInterrupt(18);
    bool call_extract_tag = false;
    uint8_t ssvalue;
    long currentmillis = millis();
    
    while (1) {
    
    ssvalue = Serial2.read(); // read 
    switch (ssvalue) {
    case -1: attachInterrupt(18, catchID, FALLING); return;                         //no data was read
    case  2: buffer_index = 0; break;                                               //RDM630/6300 found a tag => tag incoming
    case  3: call_extract_tag = true; break;                                        //extract tag at the end of the function call
    default: break;
    }//end switch
    
    buffer[buffer_index++] = ssvalue; // everything is alright => copy current value to buffer

    if (buffer_index > BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
      Serial.println("Error: Buffer overflow detected!");
      attachInterrupt(18, catchID, FALLING);
      return;
    }//end if
    
    if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        char* a=GetID();
          //studentID.publish(GetID()); //e.g: String = {"S1":"12","S2":"34"}
          Serial.println(F("Done publishing!"));
//          attachInterrupt(18, catchID, FALLING);
          while (1) {
            if ((millis()-currentmillis)>900) {
              attachInterrupt(18, catchID, FALLING);
              return;
            }//end if
          }//end while
      }//end if
      else { // something is wrong... start again looking for preamble (value: 2)
        buffer_index = 0;
        attachInterrupt(18, catchID, FALLING);
        //return;
      }//end else
    }//end if
    }//end while
    
}//end interrupt


void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial2.begin(9600); //default baudrate for RDM630/6300
  
  Wifi_begin(); // We start by connecting to a WiFi network
  mqtt.subscribe(&command); // Set up MQTT subscriptions.
  //Set up last will
 // mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN);

  pinMode(18, INPUT);
  attachInterrupt(18, catchID, FALLING);

 Serial.println("Initialize Done.");
 #ifdef DEBUG
 Serial.println("DEBUG Mode");
 #endif

}//end setup

void loop() {
  MQTT_connect();  
  
  //PUBLISH:
  //studentID.publish("123458795"); //e.g: String = {"S1":"12","S2":"34"}
  //Serial.println(F("Done publishing!"));

  //SUBCRIBE:
  // this is our 'wait for incoming subscription packets' busy subloop
   Adafruit_MQTT_Subscribe *subscription;                  
     while ((subscription = mqtt.readSubscription(5000))) {      //wait for signal
        if (subscription == &command) {                         // if something new is detected on this topic
           Execute_Command();
           }//end if
  }//end while

  if(! mqtt.ping()) { // ping the server to keep the mqtt connection alive
    mqtt.disconnect();
    }//end if
}//end loop
/////////////////////////////////////////////////////////////////////////////////////////////

void Wifi_begin() {
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print(F("Connecting to "));
  Serial.print(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
  Serial.println();
}//end wifi begin

void MQTT_connect() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).
    int8_t ret;
  // Stop if already connected.
  if (mqtt.connected()) {
      return;
  }
  Serial.print(F("Connecting to MQTT... "));


  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)           // connect will return 0 for connected
  {                                                 
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println(F("Retrying MQTT connection in 1 seconds..."));
       mqtt.disconnect();
       delay(1000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println(F("MQTT Connected!"));
}//end MQTT connect

char* GetID() {
    uint8_t *msg_data = buffer + 1; //13 byte, 10 byte data, 2 byte checksum, 1 byte tail
    #ifdef DEBUG
    uint8_t *msg_data_tag = buffer + 3; //11 byte, 8 byte data, 2 byte checksum, 1 byte tail
    #endif
    uint8_t *msg_checksum = buffer + 11; // 3 byte, 2 byte checksum, 1 byte tail
    char strID[DATA_SIZE+1];
    long checksum = 0;
    for (int i = 0; i < DATA_SIZE; i+= CHECKSUM_SIZE) {
      long val = hexstr_to_value(msg_data + i, CHECKSUM_SIZE);
      checksum ^= val;
    }//end for
    char good = (checksum == hexstr_to_value(msg_checksum, CHECKSUM_SIZE))? 1:0; //compare calculated checksum to retrieved checksum
    Serial.println();
    Serial.println(F("--------"));
    if (good==1) {//checksum return good value
      
      for (uint8_t i = 0; i < DATA_SIZE;i++) {
        strID[i] = msg_data[i];
      }//end for
      strID[DATA_SIZE]='\0';

      Serial.println(F("Checksum PASSED "));
      Serial.println(F("Card Identity: "));
      Serial.print(F("Full (HEX):   ")); 
      Serial.println((String)strID);
    
#ifdef DEBUG
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

      long tag = hexstr_to_value(msg_data_tag, DATA_TAG);
      Serial.print(F("Decimal Tag: "));
      Serial.println(tag);

      Serial.print(F("Checksum Code (HEX)(matched): "));
      for (int i = 0; i < CHECKSUM_SIZE; ++i) {
        Serial.print(char(msg_checksum[i]));
      }//end for
      Serial.println();
#endif
    }//end if
  else {//checksum return bad value
      Serial.println(F("Checksum FAILED "));
      Serial.print(F("Original Checksum code: ")); 
      for (int i = 0; i < CHECKSUM_SIZE; ++i) {
        Serial.print(char(msg_checksum[i]));
      }//end for
      Serial.println(F("Result recieved: "));
      Serial.print(checksum, HEX);Serial.println();
      Serial.println(F("Please scan your ID card again!"));
  }//end else
    Serial.println(F("--------"));
    return strID;
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
  Serial.print(F("Get command: ")); Serial.println(data);
}//end execute command

