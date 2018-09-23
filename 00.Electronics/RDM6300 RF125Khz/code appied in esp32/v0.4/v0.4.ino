// (c) Michael Schoeffler 2018, http://www.mschoeffler.de
/*
 * Modified to use with ESP32 by An Dao
 * August, 2018
 * DOIT ESP32 DEVKIT V1
 */

#define DEBUG

#define BUFFER_SIZE        14 // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
#define DATA_SIZE          10 // 10byte data (2byte version + 8byte tag)
#define CHECKSUM_SIZE    2 // 2byte checksum

#ifdef DEBUG
#define DATA_VERSION  2 // 2byte version (actual meaning of these two bytes may vary)
#define DATA_TAG      8 // 8byte tag
#endif

uint8_t buffer[BUFFER_SIZE]; // used to store an incoming data frame 
uint8_t buffer_index = 0;
void setup() {
 Serial.begin(115200); 
 Serial2.begin(9600); //default baudrate for RDM630/6300
 
 Serial.println("Initialize Done.");
 #ifdef DEBUG
 Serial.println("DEBUG Mode");
 #endif
}
void loop() {
  if (Serial2.available() > 0){
    bool call_extract_tag = false;
    
    uint8_t ssvalue = Serial2.read(); // read 

    switch (ssvalue) {
    case -1: return;                         //no data was read
    case  2: buffer_index = 0; break;        //RDM630/6300 found a tag => tag incoming
    case  3: call_extract_tag = true; break; //extract tag at the end of the function call
    default: break;
    }//end switch
    
    if (buffer_index >= BUFFER_SIZE) { // checking for a buffer overflow (It's very unlikely that an buffer overflow comes up!)
      Serial.println("Error: Buffer overflow detected!");
      return;
    }//end if
    
    buffer[buffer_index++] = ssvalue; // everything is alright => copy current value to buffer
    
    if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        extract_tag();
      }//end if
      else { // something is wrong... start again looking for preamble (value: 2)
        buffer_index = 0;
        return;
      }//end else
    }//end if
  }//end if serial available
}//end loop

void extract_tag() {
    uint8_t *msg_data = buffer + 1; //13 byte, 10 byte data, 2 byte checksum, 1 byte tail
    #ifdef DEBUG
    uint8_t *msg_data_tag = buffer + 3; //11 byte, 8 byte data, 2 byte checksum, 1 byte tail
    #endif
    uint8_t *msg_checksum = buffer + 11; // 3 byte, 2 byte checksum, 1 byte tail

    long checksum = 0;
    for (int i = 0; i < DATA_SIZE; i+= CHECKSUM_SIZE) {
      long val = hexstr_to_value(msg_data + i, CHECKSUM_SIZE);
      checksum ^= val;
    }//end for
    char good = (checksum == hexstr_to_value(msg_checksum, CHECKSUM_SIZE))? 1:0; //compare calculated checksum to retrieved checksum
    Serial.println();
    Serial.println(F("--------"));
    if (good==1) {//checksum return good value
       Serial.println(F("Checksum PASSED "));
       Serial.println(F("Identity: "));
       Serial.print(F("Full (HEX):   ")); 
       for (uint8_t i = 0; i < DATA_SIZE; ++i) {
       Serial.print(char(msg_data[i]));
       }//end for
       Serial.println();
    
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

}//end extract tag
long hexstr_to_value(unsigned char *str, unsigned int length) { // converts a hexadecimal value (encoded as ASCII string) to a numeric value
  char* copy = (char*)malloc((sizeof(char) * length) + 1); 
  memcpy(copy, str, sizeof(char) * length);
  copy[length] = '\0'; 
  // the variable "copy" is a copy of the parameter "str". "copy" has an additional '\0' element to make sure that "str" is null-terminated.
  long value = strtol(copy, NULL, 16);  // strtol converts a null-terminated string to a long value
  free(copy); // clean up 
  return value;
}
