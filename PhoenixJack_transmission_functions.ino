#include "PhoenixJack_transmission_functions.h"

/*
MILLIS: [14006] 	 [0x36B6] 	 MILLIS_CS: [0x01A1] 		RANDOM FLOAT: [146.07870483]  CONVERTED_ULong: [0x136F9100]  ConvULong_CS: [0x01AA]
MILLIS: [15006] 	 [0x3A9E] 	 MILLIS_CS: [0x01B2] 		RANDOM FLOAT: [125.75411224]  CONVERTED_ULong: [0x12397000]  ConvULong_CS: [0x0196]
MILLIS: [16007] 	 [0x3E87] 	 MILLIS_CS: [0x01A7] 		RANDOM FLOAT: [002.54639292]  CONVERTED_ULong: [0xAE16FD0]  ConvULong_CS: [0x01D7]
MILLIS: [17007] 	 [0x426F] 	 MILLIS_CS: [0x01A2] 		RANDOM FLOAT: [-30.88167000]  CONVERTED_ULong: [0x8E35D80]  ConvULong_CS: [0x01C1]
*/
char buffer[128] = "Hello, world!";  // {72, 101, 108, 108, 111, 44, 32, 119, 111, 114, 108, 100, 33, 0} should give us a checksum of 1028 or 0x404
unsigned long checksumval, coordConvertedToUlong;

unsigned long curr_millis;

float go_float_yourself = -77.025871;
String strbuffer = "";

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n\n\nTesting transmission functions");
}

void loop() {
  curr_millis = millis();                     // save the timestamp
  uint32ToCharArray(curr_millis, buffer);     // convert the unsigned long value to a char array
  checksumval = calculateChecksum32(buffer);  // calculate the checksum (4 bytes)
  sprintf(buffer, "MILLIS: [%i] \t [0x%04X] \t MILLIS_CS: [0x%04X] \t\t", curr_millis, curr_millis, checksumval);
  Serial.print(buffer);

  go_float_yourself = rand_val();                           // that's SkiCru for 'go fuck yourself'
  coordConvertedToUlong = coordToULong(go_float_yourself);  // to make our message easier to format, we'll convert it to an unsigned long with 6 decimal places; this will render as an 8byte chunk
  uint32ToCharArray(coordConvertedToUlong, buffer);         // convert the unsigned long value to a char array
  checksumval = calculateChecksum32(buffer);                // calculate the checksum (4 bytes)
  sprintf(buffer, "RANDOM FLOAT: [%012.8f]  CONVERTED_ULong: [0x%04X]  ConvULong_CS: [0x%04X]", go_float_yourself, coordConvertedToUlong, checksumval);
  Serial.println(buffer);

  delay(1000);
}

float rand_val() {
  return (float)random(-180000000, 180000000) / 1000000;
}
