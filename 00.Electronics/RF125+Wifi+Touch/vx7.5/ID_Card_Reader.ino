/*  RDM630/6300 125khz Card Reader functions
 *  (c) An Minh Dao 2018 
 *  
 *  CONTAINS:
 *  Interrupt: void catchID();
 *  
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 */

///////////////////////////////// RDM6300 INTERRUPT ///////////////////////////////////////////
void catchID() { //CAUTION: must change Watchdog Interrupt Timeout configurations to 1000ms before proceed!!
    detachInterrupt(digitalPinToInterrupt(RF_INTERRUPT));
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
            attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT), catchID, FALLING);
            return;
           }//end else
          }//end ssvalue==3 (end of signal)
          if (buffer_index > BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
            #if defined (DEBUG_BASIC) || defined (DEBUG_ADVANCE)
            Serial.println(F("Error: Buffer overflow detected!"));
            #endif
            attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT), catchID, FALLING);
            return;
          }//end if
          if (count++>13){attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT), catchID, FALLING); return;} //something is wrong so no ending signal (3) is detected (14 signal, first one have been count already, so if it bigger than 13, that means it have more than 14 elements)
        }//end while
      }//end ssvalue==2 (begin signal)

      if (count++==20) {attachInterrupt(digitalPinToInterrupt(RF_INTERRUPT), catchID, FALLING); return;} //no data was read
  }//end while
}//end interrupt
///////////////////////////////////////////////////////////////////////////////////////////////////

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
