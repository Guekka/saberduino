#pragma once

#include "base_defines.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
#include <SFML/Graphics.hpp>
#endif

class Display {
   public:
    Display();

    bool begin_frame();
    void draw_pix(Position pos, uint8_t r, uint8_t g, uint8_t b);
    void end_frame();

    static constexpr uint8_t len = 16;
#ifdef SABERDUINO_DESKTOP_COMPUTER
    static constexpr uint8_t scale = 64;

    sf::RenderWindow window_;
#else
    static constexpr uint8_t scale = 1;
#endif
};
