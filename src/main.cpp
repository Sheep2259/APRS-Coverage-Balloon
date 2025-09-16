#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>



void setup() {
  Serial.begin(115200);

}






void loop() {


  char destination[] = "APRS";
  char latitude[] = "4911.67N";
  char longitude[] = "01635.96E";
  char message[] = "vscode test DATATEST AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

  
  for (int i = 0; i < 1; i++) {
    transmit_2m(destination, latitude, longitude, message);
    delay(2000);
  }

  for (int i = 0; i < 1; i++) {
    transmit_lora(destination, latitude, longitude, message);
    delay(2000);
  }

}

