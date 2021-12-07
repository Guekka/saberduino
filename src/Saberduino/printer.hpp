#ifndef SABERDUINO_PRINTER
#define SABERDUINO_PRINTER

#include "base_defines.hpp"

class Printer {
   public:
    Printer();

    template <typename T>
    void print(T val) {
#ifdef AVR
        Serial.print(val);
#else
        std::cout << val;
#endif
    }

    template <typename T>
    void println(T val) {
#ifdef AVR
        Serial.println(val);
#else
        std::cout << val << '\n';
#endif
    }
};

static Printer printer;

#endif
