#ifndef SABERDUINO_BASE_DEFINES
#define SABERDUINO_BASE_DEFINES

#ifdef SABERDUINO_DESKTOP_COMPUTER  // Assume Arduino available
#include <cstdint>
#include <iostream>
#else
#include "Arduino.h"
#endif

struct Position {
    uint8_t x;
    uint8_t y;
};

#endif
