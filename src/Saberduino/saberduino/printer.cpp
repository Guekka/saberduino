#include "printer.hpp"

Printer::Printer() {
#ifndef SABERDUINO_DESKTOP_COMPUTER
    Serial.begin(9600);
#endif
}
