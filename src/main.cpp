#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>
#include <rpi_defs.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <GPS.h>
#include <globals.h>
#include <BigNumber.h>
#include <tuple>
#include <vector>

int batvoltage;
int solarvoltage;
int counter = 0;
int seconds;

float lat = 0.0f, lng = 0.0f, age_s = -1.0f;
float alt = 0.0f, speed_kmh = -1.0f, course_deg = -1.0f, hdop = -1.0f;
uint16_t year = 0;
uint8_t month = 0, day = 0, hour = 0, minute = 0, second = 0, centisecond = 0, sats = 0;


// structure of the data that we feed into the mixed radix encoder (not done)
std::vector<std::tuple<uint16_t, uint16_t>> digits_and_bases = {
    //{frequency, 1}, // 0 for vhf (2m), 1 for uhf (lora)
    {second, 60},
    {sats, 40},
    {alt, 14000},
    {}
};





void setup() {
  Serial.begin(115200);
  Serial.print("test");
  
  SPI.setRX(sxMISO_pin); // MISO
  SPI.setTX(sxMOSI_pin); // MOSI
  SPI.setSCK(sxSCK_pin); // SCK
  SPI.setCS(sxCS_pin);   // CSn
  SPI.begin();

  analogReadResolution(12);
  
  ss.begin(GPSBaud);

  BigNumber::begin ();

}


void loop() {
  char callsign[] = "M7CWV";
  char destination[] = "APRS";
  char latitude[] = "4911.67N";
  char longitude[] = "01635.96E";
  char messagelora[] = "lora transmission";
  char message2m[] = "2m transmission";



  solarvoltage = analogRead(vsensesolar_pin);
  batvoltage = analogRead(vsensebat_pin);
  int uptime = millis() / 1000;

  sprintf(messagelora, "u,S%d,B%d,T%d,C%d", solarvoltage, batvoltage, uptime, counter);
  sprintf(message2m, "v,S%d,B%d,T%d,C%d", solarvoltage, batvoltage, uptime, counter);

  //Serial.print(messagelora);
  //Serial.print(message2m);

  // SEE README FOR INSTRUCTIONS

  /*
  for (int i = 0; i < 3; i++) {
    transmit_2m(callsign, destination, latitude, longitude, message2m);
    delay(100);
    transmit_2m(callsign, destination, latitude, longitude, message2m);
    delay(6000);

    counter++;
  }
  */


  	// This sketch displays information every time a new sentence is correctly encoded.
	while (ss.available() > 0) {
		if (gps.encode(ss.read())) {
			  displayInfo(lat, lng, age_s,
              year, month, day,
              hour, minute, second, centisecond,
              alt, speed_kmh, course_deg,
              sats, hdop);

  Serial.print("Lat: "); Serial.println(lat, 6);
  Serial.print("Lng: "); Serial.println(lng, 6);
  Serial.print("Age (s): "); Serial.println(age_s, 2);
  Serial.print("Date: "); Serial.print(day); Serial.print("/"); Serial.print(month); Serial.print("/"); Serial.println(year);
  Serial.print("Time (UTC): ");
  Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":"); Serial.println(second);
  Serial.print("Alt (m): "); Serial.println(alt, 2);
  Serial.print("Speed (km/h): "); Serial.println(speed_kmh, 2);
  Serial.print("Course (deg): "); Serial.println(course_deg, 2);
  Serial.print("Satellites: "); Serial.println(sats);
  Serial.print("HDOP: "); Serial.println(hdop, 2);

  delay(1000);
      
		}
	}
}






