/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ArduinoJson.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "Home"
#define WLAN_PASS       "minhan74"

/************************* MQTT Client Setup *********************************/

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

/***************************** Global State  *********************************/
// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS);

/****************************** Initialize Feeds ***************************************/
//PUBLISH
Adafruit_MQTT_Publish studentID = Adafruit_MQTT_Publish(&mqtt,"B1/101/ID",MQTT_QOS_1);

//SUBCRIBE
Adafruit_MQTT_Subscribe command = Adafruit_MQTT_Subscribe(&mqtt,"B1/101/command",MQTT_QOS_1);

void setup() {
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  delay(10); 
  Wifi_begin(); // We start by connecting to a WiFi network
  // Set up MQTT subscriptions.
  mqtt.subscribe(&command);

  //Set up last will
 // mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN);

}//end setup

void loop() {
  MQTT_connect();
  //PUBLISH:


  //SUBCRIBE:
  // this is our 'wait for incoming subscription packets' busy subloop
   Adafruit_MQTT_Subscribe *subscription;                  
     while ((subscription = mqtt.readSubscription(5000))) {      //wait for signal
        if (subscription == &command) {                         // if something new is detected on this topic
           Execute_Command();
           }//end if
  else {studentID.publish("123458795"); //e.g: String = {"S1":"12","S2":"34"}
  Serial.println(F("Done publishing!"));
  }
  }//end while
  
  if(! mqtt.ping()) { // ping the server to keep the mqtt connection alive
    mqtt.disconnect();
    }//end if
}//end loop

void Execute_Command() {
  String data = (char*)command.lastread;   // Function to analize the string
  Serial.print(F("Get command: ")); Serial.println(data);
}//end execute command

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
       Serial.println(F("Retrying MQTT connection in 5 seconds..."));
       mqtt.disconnect();
       delay(2000);  // wait 2 seconds
       retries--;
       if (retries == 0) {
         while (1);
       }
  }
  Serial.println(F("MQTT Connected!"));
}//end MQTT connect
