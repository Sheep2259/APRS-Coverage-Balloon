#include <RadioLib.h>
#include <Arduino.h>
#include <SPI.h>
#include <radio.h>
#include <rpi_defs.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

int batvoltage;
int solarvoltage;
int counter = 0;
int seconds;

TinyGPSPlus gps;
SoftwareSerial ss(gpsRXPin, gpsTXPin);




// helper: convert degrees to cardinal direction (N, NNE, NE, ...)
const char* cardinalFromDeg(float deg) {
  if (!isfinite(deg)) return "---";
  static const char* cardinals[] = {
    "N","NNE","NE","ENE","E","ESE","SE","SSE",
    "S","SSW","SW","WSW","W","WNW","NW","NNW"
  };
  // normalize
  while (deg < 0) deg += 360.0;
  while (deg >= 360.0) deg -= 360.0;
  int idx = (int)((deg + 11.25) / 22.5) & 15; // 360/16 = 22.5
  return cardinals[idx];
}

void displayInfo() {
  // --- Location ---
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);

    // age of the last location fix in seconds
    unsigned long ageMs = gps.location.age(); // milliseconds
    Serial.print(F(" (age "));
    if (ageMs == ULONG_MAX) {
      Serial.print(F("N/A"));
    } else {
      Serial.print(ageMs / 1000.0, 2);
      Serial.print(F("s"));
    }
    Serial.print(F(")"));
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Date / Time (UTC) ---
  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Altitude ---
  Serial.print(F("  Altitude: "));
  if (gps.altitude.isValid()) {
    float alt_m = gps.altitude.meters();
    float alt_ft = alt_m * 3.280839895; // 1 m = 3.280839895 ft
    Serial.print(alt_m, 2);
    Serial.print(F(" m / "));
    Serial.print(alt_ft, 2);
    Serial.print(F(" ft"));
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Speed ---
  Serial.print(F("  Speed: "));
  if (gps.speed.isValid()) {
    float kmh = gps.speed.kmph();               // km/h
    float knots = kmh / 1.852f;                 // 1 knot = 1.852 km/h
    float mph = kmh * 0.621371192f;             // 1 km/h = 0.621371192 mph
    Serial.print(kmh, 2);
    Serial.print(F(" km/h ("));
    Serial.print(mph, 2);
    Serial.print(F(" mph, "));
    Serial.print(knots, 2);
    Serial.print(F(" kn)"));
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Course / Bearing ---
  Serial.print(F("  Course: "));
  if (gps.course.isValid()) {
    float deg = gps.course.deg();
    Serial.print(deg, 2);
    Serial.print(F(" deg ("));
    Serial.print(cardinalFromDeg(deg));
    Serial.print(F(")"));
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Satellites and HDOP (precision) ---
  Serial.print(F("  Sats: "));
  if (gps.satellites.isValid()) {
    Serial.print(gps.satellites.value());
  } else {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  HDOP: "));
  if (gps.hdop.isValid()) {
    // hdop.hdop() returns a float HDOP; print with two decimals
    Serial.print(gps.hdop.hdop(), 2);
  } else {
    Serial.print(F("INVALID"));
  }

  // --- Library diagnostics (optional, good for debugging) ---
  Serial.print(F("  Stats: chars "));
  Serial.print(gps.charsProcessed());
  Serial.print(F("  sentencesWithFix "));
  Serial.print(gps.sentencesWithFix());
  Serial.print(F("  failedCS "));
  Serial.print(gps.failedChecksum());

  Serial.println();
}








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

  // the following things must be transmitted periodically:
  // a range of packet lengths to test how many characters are usable,
  // packets with a wide veriaty of characters so we can tell which ones can be used for encoding,
  // packets in clusters, as in many consecutive transmission in a row to test large data thoughputs

  // Mixed radix encoding should probably be used, same as big number encoding on traquito wspr

  // aprs may have a comment message limit of 67 chars, although not certain
  // i think aprs has a min 5s between packets
  // so possibly test alternating callsign to bypass

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
			displayInfo();
      
		}
	}

	if (millis() > 5000 && gps.charsProcessed() < 10) {
		Serial.println(F("No GPS detected: check wiring."));
		while(true);
	}

}






