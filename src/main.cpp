#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>



void setup() {
  Serial.begin(115200);

}






void loop() {
  
  transmit_lora();
  delay(4000);
  transmit_2m();
  delay(4000);

}

