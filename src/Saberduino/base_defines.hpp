#ifndef SABERDUINO_BASE_DEFINES
#define SABERDUINO_BASE_DEFINES

#ifdef AVR  // Assume Arduino available
#include "Arduino.h"
#else
#include <cstdint>
#include <iostream>
#endif

struct Position {
    uint8_t x;
    uint8_t y;
};

#endif
