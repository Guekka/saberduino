#include "saber.hpp"
#include "printer.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
#include <SFML/Graphics.hpp>
#endif

void Saber::init() {
    printer.println("init saber");
}

Position Saber::position() {
#ifdef SABERDUINO_DESKTOP_COMPUTER
    const auto raw = sf::Mouse::getPosition();
#endif

    printer.println("position saber");
    return Position{0, 0};
}
