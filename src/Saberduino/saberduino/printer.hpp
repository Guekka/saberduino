#ifndef SABERDUINO_PRINTER
#define SABERDUINO_PRINTER

#include "base_defines.hpp"

class Printer {
   public:
    Printer();

    template <typename T>
    void print(T val) {
#ifdef SABERDUINO_DESKTOP_COMPUTER
        std::cout << val;
#else
        Serial.print(val);
#endif
    }

    template <typename T>
    void println(T val) {
#ifdef SABERDUINO_DESKTOP_COMPUTER
        std::cout << val << '\n';
#else
        Serial.println(val);
#endif
    }
};

static Printer printer;

#endif
