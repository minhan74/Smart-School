#ifndef EEPROM_WIFI_ACCESS_H
#define EEPROM_WIFI_ACCESS_H

#include "EEPROM.h"

#ifndef CONFIG_H
//#define CONFIG_H
#include "config.h"
#endif
/************************* WiFi Access Point *********************************/
const char PROGMEM EEPROM_SIZE = 64;
String WLAN_SSID;
String WLAN_PASS;
char Wifi_idlength;
char Wifi_passlength;
char signalReset=0;


void gettingEEPROM();
void ResetID();
String GetData();
void savingEEPROM();
void Wifi_begin();

#endif // EEPROM_WIFI_ACCESS_H
