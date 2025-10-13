#ifndef GLOBALS_H
#define GLOBALS_H

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// Declare the objects with 'extern'
// This tells other files that these objects exist somewhere else.
extern TinyGPSPlus gps;
extern SoftwareSerial ss;

#endif