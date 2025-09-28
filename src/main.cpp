#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>
#include <rpi_defs.h>


void setup() {
  Serial.begin(115200);
  Serial.print("test");
  
  SPI.setRX(sxMISO_pin); // MISO
  SPI.setTX(sxMOSI_pin); // MOSI
  SPI.setSCK(sxSCK_pin); // SCK
  SPI.setCS(sxCS_pin);   // CSn
  SPI.begin();
}






void loop() {
  char callsign[] = "M7CWV";
  char destination[] = "APRS";
  char latitude[] = "4911.67N";
  char longitude[] = "01635.96E";
  char messagelora[] = "lora transmission";
  char message2m[] = "2m transmission";

  
  for (int i = 0; i < 1; i++) {
    transmit_2m(callsign, destination, latitude, longitude, message2m);
    delay(2000);
  }

  for (int i = 0; i < 1; i++) {
    transmit_lora(callsign, destination, latitude, longitude, messagelora);
    delay(2000);
  }

}

