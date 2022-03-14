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

    friend bool operator==(Position a, Position b) { return a.x == b.x && a.y == b.y; }
};

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

constexpr uint16_t to_millis_scaled(uint64_t millis)
{
    return static_cast<uint16_t>(millis / 32);
}

inline uint16_t milli_scaled()
{
#ifdef SABERDUINO_DESKTOP_COMPUTER
    using namespace std::chrono;
    static const auto start = steady_clock::now();
    const auto now = steady_clock::now();
    const auto millis = duration_cast<milliseconds>(now - start);
    return to_millis_scaled(millis.count());
#else
    return to_millis_scaled(millis());
#endif
}

inline void sleep_milli(uint16_t millis) {
#ifdef SABERDUINO_DESKTOP_COMPUTER
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#else
    delay(millis);
#endif
}

#ifndef PROGMEM
#define PROGMEM
#endif

template<typename T, uint8_t Size>
class CircularBuffer
{
    T data_[Size];
    T *cur_;

public:
    CircularBuffer()
        : cur_(data_)
    {
    }

    void push(const T &elem)
    {
        *cur_ = elem;
        if (++cur_ == data_ + Size)
            cur_ = data_;
    }

    T &operator[](uint8_t idx) { return data_[idx]; }

    uint8_t size() { return Size; }
};

#ifdef SABERDUINO_DESKTOP_COMPUTER
template<typename Ptr>
char pgm_read_byte_near(Ptr *data)
{
    return *reinterpret_cast<const char *>(data);
}
#endif

#endif
