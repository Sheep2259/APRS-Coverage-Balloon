#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>



void setup() {
  Serial.begin(115200);

}






void loop() {
  
  for (int i = 0; i < 1; i++) {
    transmit_lora();
    delay(2000);
  }

  for (int i = 0; i < 1; i++) {
    transmit_2m();
    delay(2000);
  }

}

