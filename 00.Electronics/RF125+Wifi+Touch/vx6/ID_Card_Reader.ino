/*  RDM630/6300 125khz Card Reader functions
 *  (c) An Minh Dao 2018 
 *  
 *  CONTAINS:
 *  void GetID();
 *  long hexstr_to_value(unsigned char *str, unsigned int str_length);
 */
 
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
