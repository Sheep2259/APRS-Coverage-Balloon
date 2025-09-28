// Contains pin definitions for rpi 2040
#pragma once


// SX1278 has the following connections:
// NSS pin:   16
// DIO0 pin:  2
// RESET pin: 17
// DIO1 pin:  5
// SX1278 radio = new Module(16, 2, 17, 5);
// For 2m aprs, uses DIO2 connected to 21


// sx1278 pin defs
constexpr int sxSCK_pin = 2;  // 2, 6, 18, 22  } alternative pins
constexpr int sxMOSI_pin = 3;     // 3, 7, 19, 23  } 
constexpr int sxMISO_pin = 0;     // 0, 4, 16, 20  }
constexpr int sxCS_pin = 1;       // 1, 5, 17, 21  }

constexpr int sxNSS_pin = 16;
constexpr int sxDIO0_pin = 2;
constexpr int sxRESET_pin = 17;
constexpr int sxDIO1_pin = 15;
constexpr int sxDIO2_pin = 21;


// gps pin defs
constexpr int gpsTX_pin = 8;
constexpr int gpsRX_pin = 9;


// other pin defs
constexpr int vsense_pin = 26;

