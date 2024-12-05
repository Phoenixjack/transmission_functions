// RECEIVE FUNCTIONS

struct MyData {  // assumes a 4 byte hex value of EPOCH_sec, followed by a 4 byte signed float value
  unsigned long hexValue;
  float floatValue;
};

MyData parseString(String rcvbuffer) {
  MyData data;

  // Extract hexadecimal value
  String hexString = rcvbuffer.substring(0, 4);
  data.hexValue = strtoul(hexString.c_str(), nullptr, 16);

  // Extract float value
  String floatString = rcvbuffer.substring(4, 8);
  data.floatValue = atof(floatString.c_str());

  return data;
}

MyData parseCharArray(const char* rcvbuffer) {
  MyData data;

  // Extract hexadecimal value
  data.hexValue = strtoul(rcvbuffer, nullptr, 16);

  // Extract float value
  data.floatValue = atof(rcvbuffer + 4);

  return data;
}

// TRANSMIT FUNCTIONS

void uint8ToCharArray(uint8_t value, char* charbuffer) {
  sprintf(charbuffer, "%02X", value);
}

void int8ToCharArray(int8_t value, char* charbuffer) {
  sprintf(charbuffer, "%02X", value);
}

void uint16ToCharArray(uint16_t value, char* charbuffer) {
  sprintf(charbuffer, "%04X", value);
}

void int16ToCharArray(int16_t value, char* charbuffer) {
  sprintf(charbuffer, "%04X", value);
}

void uint32ToCharArray(uint32_t value, char* charbuffer) {
  sprintf(charbuffer, "%08X", value);
}

void int32ToCharArray(int32_t value, char* charbuffer) {
  sprintf(charbuffer, "%08X", value);
}

void floatToCharArray(float value, char* charbuffer) {  // renders (-)3.8 with leading and trailing zeroes
  sprintf(charbuffer, "%012.8f", value);
}

unsigned long coordToULong(float value) {  // make everything positive, include 6 decimal places; should result in max value of 359,999,999 (0x157529FF)
  return (value + 180) * 1000000;
}
// https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/
uint8_t calculateChecksum8(char* data) {
  uint8_t k = 0, mychecksum = 0;
  do {
    mychecksum += (uint8_t)data[k];
    k++;
  } while (k < 256 && (uint8_t)data[k] != 0);
  return mychecksum;
}

uint16_t calculateChecksum16(char* data) {
  uint8_t k = 0;
  uint16_t mychecksum = 0;
  do {
    mychecksum += (uint8_t)data[k];
    k++;
  } while (k < 256 && (uint8_t)data[k] != 0);
  return mychecksum;
}

uint16_t calculateChecksum16(String* datastr) {
  uint8_t k = datastr->length();
  uint16_t mychecksum = 0;
  for (uint8_t i = 0; i < k; i++) {
    mychecksum += (uint8_t)datastr->charAt(i);
  }
  return mychecksum;
}

uint32_t calculateChecksum32(char* data) {
  uint8_t k = 0;
  uint32_t mychecksum = 0;
  do {
    mychecksum += (uint8_t)data[k];
    k++;
  } while (k < 256 && (uint8_t)data[k] != 0);
  return mychecksum;
}

/*
  for (uint8_t i = 0; i < 13; i++) {
    Serial.print(buffer[i]);  // (char)
    if (buffer[i + 1] == '\0') { i = 20; }
  }

*/