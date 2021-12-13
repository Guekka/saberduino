#include "saber.hpp"
#include "printer.hpp"

void Saber::init() {
    printer.println("init saber");
}

Position Saber::position() {
    printer.println("position saber");
    return Position{0, 0};
}
