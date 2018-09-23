/*  MQTT Wifi Changeable functions file
 *  (c) An Minh Dao 2018
 *  
 *  CONTAINS:
 *  void Wifi_begin();
 *  void MQTT_connect();
 *  void ResetID();
 *  String GetData();
 *  void gettingEEPROM();
 *  void savingEEPROM();
 */
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

//--------SELF CREATED QOS1
void publishNow(Adafruit_MQTT_Publish topicPub,const char* MQTTmessage, const char* failed, const char* sucess) {
  char pub=1;
  #if not defined (DEBUG_BASIC) || not defined (DEBUG_ADVANCE)
  while (!topicPub.publish(MQTTmessage)) {delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  #endif
  #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
  
  while (!topicPub.publish(MQTTmessage)) {Serial.println(F(failed));delay(PUB_WAIT);if (pub++>(PUB_RETRIES-1)) break;} 
  if (pub<(PUB_RETRIES))                 {Serial.println(F(sucess));}
  //*/
  #endif
}//end publishNow


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
