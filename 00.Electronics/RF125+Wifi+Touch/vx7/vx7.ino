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
Adafruit_MQTT_Publish ID = Adafruit_MQTT_Publish(&mqtt,ID_FEED,MQTT_QOS_1);
Adafruit_MQTT_Publish facility = Adafruit_MQTT_Publish(&mqtt,FACILITY_FEED,MQTT_QOS_1);
//SUBCRIBE
Adafruit_MQTT_Subscribe command = Adafruit_MQTT_Subscribe(&mqtt,COMMAND_FEED,MQTT_QOS_1);


/************************************* INTERRUPT **********************************************/
/////////////////////////////// TOUCH BUTTON INTERRUPT ////////////////////////////////////////
void gotTouch() {
  if (roomON==true) { //open the pheripheral box (power the solenoid)
    digitalWrite(SOLENOID,HIGH);
    lastmillis_touch = millis();
  }//end if
}//end gotTouch
///////////////////////////////// RDM6300 INTERRUPT ///////////////////////////////////////////
void IRAM_ATTR catchID() { //CAUTION: must change Watchdog Interrupt Timeout configurations to 1000ms before proceed!!
    detachInterrupt(RF_INTERRUPT);
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
            attachInterrupt(RF_INTERRUPT, catchID, FALLING);
            return;
           }//end else
          }//end ssvalue==3 (end of signal)
          if (buffer_index > BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
            #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
            Serial.println(F("Error: Buffer overflow detected!"));
            #endif
            attachInterrupt(RF_INTERRUPT, catchID, FALLING);
            return;
          }//end if
          if (count++>13){attachInterrupt(RF_INTERRUPT, catchID, FALLING); return;} //something is wrong so no ending signal (3) is detected (14 signal, first one have been count already, so if it bigger than 13, that means it have more than 14 elements)
        }//end while
      }//end ssvalue==2 (begin signal)

      if (count++==20) {attachInterrupt(RF_INTERRUPT, catchID, FALLING); return;} //no data was read
  }//end while
}//end interrupt
//////////////////////////////////MICRO AND REMOTE DETACHED INTERRUPT/////////////////////////
void IRAM_ATTR microDetached() {
  
}//end microDetached

void IRAM_ATTR remoteDetached() {
  
}//end remoteDetached
//////////////////////////////////////////////////////////////////////////////////////////////

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
 #if not defined (DEBUG_BASIC) || not defined (DEBUG_ADVANCE)
 facility.publish("online");
 #endif
 #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
 if (! facility.publish("online")) {Serial.println(F("Status Failed to update!"));} 
 else                              {Serial.println(F("Status updated!"));}
 #endif
//--------------RF INITIALIZE---------------------
 Serial2.begin(9600); //default baudrate for RDM630/6300
 pinMode(RF_INTERRUPT, INPUT);
 attachInterrupt(RF_INTERRUPT,catchID, FALLING);

//--------------TOUCH INITIALIZE---------------------
 touchAttachInterrupt(TOUCH_PIN,gotTouch, THRESHOLD);

//--------------PINOUT INITIALIZE---------------------
 pinMode(MAIN_RELAY, OUTPUT);
 pinMode(SOLENOID, OUTPUT);
 digitalWrite(MAIN_RELAY,LOW);
 digitalWrite(SOLENOID,LOW);

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
    attachInterrupt(RF_INTERRUPT,catchID, FALLING);
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
  if((! mqtt.ping())&&((millis()-lastmillis)>45000)) { // ping the server to keep the mqtt connection alive
    lastmillis = millis(); //45second
    mqtt.disconnect();
    }//end if
}//end loop
/////////////////////////////////////////////////////////////////////////////////////////////

void Execute_Command() {
  String data = (char*)command.lastread;   // Function to analize the string
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  Serial.print(F("Get command: ")); Serial.println(data);
  #endif
  if (data=="on") {digitalWrite(MAIN_RELAY,HIGH);roomON=true;} //on
  if (data=="off"){digitalWrite(MAIN_RELAY,LOW);roomON=false;} //off

}//end execute command
