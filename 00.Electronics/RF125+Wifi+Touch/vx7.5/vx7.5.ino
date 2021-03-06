/*  SMART SCHOOL SYSTEM - MASTER FILE
 *  (c) An Minh Dao 2018 
 */

#define DEBUG_BASIC
#define DEBUG_ADVANCE

#include "config.h"
/******** Global State  ********/
WiFiClient client; // Create an ESP32 WiFiClient class to connect to the MQTT server.
Adafruit_MQTT_Client mqtt(&client, SERVER, PORT, CLIENT_ID, USERNAME, PASS); // Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.

/******** Initialize Feeds ********/
//PUBLISH
Adafruit_MQTT_Publish ID = Adafruit_MQTT_Publish(&mqtt,ID_FEED,MQTT_QOS_0);
Adafruit_MQTT_Publish facility = Adafruit_MQTT_Publish(&mqtt,FACILITY_FEED,MQTT_QOS_0);
//SUBCRIBE
Adafruit_MQTT_Subscribe command = Adafruit_MQTT_Subscribe(&mqtt,COMMAND_FEED,MQTT_QOS_1);


/************************************* INTERRUPT **********************************************/
/////////////////////////////// TOUCH BUTTON INTERRUPT ////////////////////////////////////////
void IRAM_ATTR gotTouch() {
  if (roomON==true) { //open the pheripheral box (power the solenoid)
    digitalWrite(SOLENOID,HIGH);
    lastmillis_touch = millis();
  }//end if
}//end gotTouch

void setup() {
 WiFi.mode(WIFI_STA);
 #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
 Serial.begin(115200);
 #endif
//--------------WIFI AND MQTT INITIALIZE---------------------
 EEPROM.begin(EEPROM_SIZE);
 gettingEEPROM(); //leave it here for temporary id and password wifi, DO NOT MOVE BELOW WFconnect
 WFconnect:
 Wifi_begin(); // We start by connecting to a WiFi network
 ResetID();
 if (signalReset==1) {signalReset=0; goto WFconnect;}

 mqtt.will (LWT_TOPIC, LWT_PAYLOAD, MQTT_QOS_1, LWT_RETAIN); //Set up last will
 mqtt.subscribe(&command); // Set up MQTT subscriptions.

 MQTT_connect();
 lastmillis = millis();
 publishNow(facility,"online","Status Failed to update!","Status updated!");
//--------------RF INITIALIZE---------------------
 Serial2.begin(9600); //default baudrate for RDM630/6300
 pinMode(RF_INTERRUPT, INPUT);
 attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT),catchID, FALLING);

//--------------TOUCH INITIALIZE---------------------
 touchAttachInterrupt(digitalPinToInterrupt(TOUCH_PIN),gotTouch, THRESHOLD);

//--------------PINOUT INITIALIZE---------------------
 pinMode(MAIN_RELAY, OUTPUT);
 pinMode(SOLENOID, OUTPUT);
 digitalWrite(MAIN_RELAY,LOW);
 digitalWrite(SOLENOID,LOW);

 pinMode(MICRO_PIN,INPUT);
 pinMode(REMOTE_PIN,INPUT);

//--------------FINALIZING FOR DEBUG MODE---------------------
 #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
 Serial.println(F("Initialize Done."));
 #endif
 #ifdef DEBUG_ADVANCE
 Serial.println(F("ADVANCED DEBUG Mode"));
 #endif

}//end setup

void loop() {
  MQTT_connect();
  
  
  if (gotID) {
    gotID=false;
    publishNow(ID,strID,"Failed!","Published!");
    Serial2.begin(9600);
    attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT),catchID, FALLING);
  }//end if gotID


  //SUBCRIBE:
  // this is our 'wait for incoming subscription packets' busy subloop. Max is 15 subs at a time, change at Adafruit_MQTT.h, #define MAXSUBSCRIPTIONS 15
   Adafruit_MQTT_Subscribe *subscription;                  
     while ((subscription = mqtt.readSubscription(1000))) {      //wait for signal
        if (subscription == &command) {                         // if something new is detected on this topic
           Execute_Command();
           }//end if
  }//end while

  if ((millis()-lastmillis_touch)>1000) {digitalWrite(SOLENOID,LOW);} //take advantages of the waiting time of the subcribe loop

  // Adjust PING time in seconds in Adafruit_MQTT.h:  
  //#define MQTT_CONN_KEEPALIVE 60 --> Default to 1 minutes.
  if (((millis()-lastmillis)>45000)) {//45second
  if(! mqtt.ping()) { // ping the server to keep the mqtt connection alive
    lastmillis = millis();
    mqtt.disconnect();
   }//end if
  }//end if
}//end loop
/////////////////////////////////////////////////////////////////////////////////////////////

void Execute_Command() {
  String data = (char*)command.lastread;   // Function to analize the string
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.print(F("Get command: ")); Serial.println(data);
  #endif
  if (data=="on") {digitalWrite(MAIN_RELAY,HIGH);roomON=true;} //on
  if (data=="off"){
    if(digitalRead(MICRO_PIN)&&digitalRead(REMOTE_PIN)) {publishNow(facility, "good","Failed!","Published!");}//end if
    else {publishNow(facility, "bad","Failed!","Published!");}
    digitalWrite(MAIN_RELAY,LOW);
    roomON=false;
    } //end if off
}//end execute command
