/*  RDM630/6300 + WIFI+ Touch - config file
 *  (c) An Minh Dao 2018 
 */

#ifndef CONFIG_H
#define CONFIG_H
////////////////////////////////////////COMMUNICATION SETUP//////////////////////////////////
#include "WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/******** pinout define *************/
#define    TOUCH_PIN               T0
const char RF_INTERRUPT PROGMEM =  18;
const char MAIN_RELAY   PROGMEM =  23;
const char SOLENOID     PROGMEM =  22;

/******** WiFi Access Point *********/
//CHANGED LOCATION TO EEPROM_WIFI_ACCESS
//const char WLAN_SSID[]  PROGMEM = "Home";
//const char WLAN_PASS[]  PROGMEM = "minhan74";

#include "EEPROM.h"
const char PROGMEM EEPROM_SIZE = 64;
String WLAN_SSID;
String WLAN_PASS;
char Wifi_idlength;
char Wifi_passlength;
char signalReset=0;

/******** MQTT Client Setup **********/

const char SERVER[]      PROGMEM = "m11.cloudmqtt.com";
const int  PORT          PROGMEM =  12180;      // use 22180 for SSL
const char USERNAME[]    PROGMEM = "bmlflxes";
const char PASS[]        PROGMEM = "Mj8LHanZvdkf";
const char CLIENT_ID[]   PROGMEM = "B1/101";

const char LWT_TOPIC[]   PROGMEM = "B1/101/facility";
const char LWT_PAYLOAD[] PROGMEM = "offline";
const char LWT_RETAIN    PROGMEM =  0;         //The broker will store the last message as the last known good value
//MQTT_CONN_KEEPALIVE is defined inside the Adafruit_MQTT.h (default 5 minutes) --> need to change to 15 min (900)
//CLEAN_SESSION is defined as TRUE as always clean the session

const char ID_FEED[]       PROGMEM = "B1/101/ID";
const char FACILITY_FEED[] PROGMEM = "B1/101/facility";
const char COMMAND_FEED[]  PROGMEM = "B1/101/command";
const char PUB_RETRIES     PROGMEM = 50;
const char PUB_WAIT        PROGMEM = 250;
///////////////////////////RDM6300/6300 125Khz SETUP//////////////////////////////////////////


const char BUFFER_SIZE   PROGMEM = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const char DATA_SIZE     PROGMEM = 10; // 10byte data (2byte version + 8byte tag)
const char CHECKSUM_SIZE PROGMEM = 2;  // 2byte checksum

#if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
const char DATA_VERSION PROGMEM = 2; // 2byte version (actual meaning of these two bytes may vary)
const char DATA_TAG     PROGMEM = 8; // 8byte tag
#endif

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame 
uint8_t buffer_index = 0;

boolean gotID = false;
boolean roomON = false;
char strID[DATA_SIZE+1];
unsigned long lastmillis;
unsigned long lastmillis_touch;

///////////////////////////TOUCH BUTTON INTERRUPT SETUP//////////////////////////////////////////

const char THRESHOLD PROGMEM = 10; // the bigger the threshold, the more sensible is the touch

///////////////////////////MICRO AND REMOTE CHECKING PIN//////////////////////////////////////////

const char MICRO_PIN PROGMEM = 15; 
const char REMOTE_PIN PROGMEM = 2; 


#endif //CONFIG_H
