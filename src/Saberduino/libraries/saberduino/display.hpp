#pragma once

#include "base_defines.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
#include <SFML/Graphics.hpp>
#else
#include <RGBmatrixPanel.h>
#endif

class Display {
   public:
    Display();

    void init();

    bool begin_frame();
    void draw_square(Position center, Color c, uint8_t size);
    void draw_line(Position start, Position end, Color c);
    void end_frame();

private:
    static constexpr uint8_t width = 64;
    static constexpr uint8_t height = 32;
#ifdef SABERDUINO_DESKTOP_COMPUTER
    static constexpr uint8_t scale = 16;

    sf::RenderWindow window_;
#else
    static constexpr uint8_t scale = 1;
    RGBmatrixPanel window_;
#endif
};
