#ifndef SABERDUINO_BASE_DEFINES
#define SABERDUINO_BASE_DEFINES

#ifdef SABERDUINO_DESKTOP_COMPUTER  // Assume Arduino available
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>
#else
#include "Arduino.h"
#endif

struct Position {
    uint8_t x;
    uint8_t y;
};

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

inline uint16_t to_millis_scaled(uint64_t millis) {
    return static_cast<uint16_t>(millis / 32);
}

inline uint64_t milli_scaled() {
#ifdef SABERDUINO_DESKTOP_COMPUTER
    using namespace std::chrono;
    static const auto start = steady_clock::now();
    const auto now = steady_clock::now();
    const auto millis = duration_cast<milliseconds>(now - start);
    return to_millis_scaled(millis.count());
#else
    return millis() / 20;
#endif
}

inline void sleep_milli(uint16_t millis) {
#ifdef SABERDUINO_DESKTOP_COMPUTER
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#else
    delay(millis);
#endif
}

#endif
