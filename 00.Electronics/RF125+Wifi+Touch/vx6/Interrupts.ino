/*  Interrupts functions for SMART SCHOOL SYSTEM
 *  (c) An Minh Dao 2018 
 *  
 *  CONTAINS:
 *  void gotTouch(); // touch button interrupt
 *  void IRAM_ATTR catchID(); // RDM6300 125khz interrupt
 *  void IRAM_ATTR microDetached()
 *  void IRAM_ATTR remoteDetached()
 *

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
//////////////////////////////////MICRO AND REMOTE DETACHED INTERRUPT/////////////////////////
void IRAM_ATTR microDetached() {
  
}//end microDetached

void IRAM_ATTR remoteDetached() {
  
}//end remoteDetached
*/
