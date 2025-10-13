#include <Arduino.h>
#include <rpi_defs.h>
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>


TinyGPSPlus gps;
SoftwareSerial ss(gpsRXPin, gpsTXPin);






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




