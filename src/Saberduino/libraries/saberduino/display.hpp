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
    void end_frame();

    void draw_line(Position start, Position end, Color c);

    void draw_square(Position center, Color c, uint8_t size);
    void fill_rect(Position topleft, Color c, uint8_t w, uint8_t h);

    void draw_cube(Position topleft, uint8_t size, Color frontc, Color backc);

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
