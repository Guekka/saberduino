#include "printer.hpp"

Printer::Printer() {
#ifdef AVR
    Serial.begin(9600);
#endif
}
