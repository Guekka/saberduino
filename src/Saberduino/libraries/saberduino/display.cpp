#include "display.hpp"

#ifdef SABERDUINO_DESKTOP_COMPUTER
Display::Display()
    : window_(sf::VideoMode(width * scale, height * scale), "Saberduino") {}

bool Display::begin_frame() {
    if (!window_.isOpen())
        return false;

    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window_.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window_.close();
    }

    // clear the window with black color
    window_.clear(sf::Color::White);

    return true;
}

void Display::draw_square(Position center, Color c, uint8_t size) {
    center.x *= scale;
    center.y *= scale;
    size *= scale;

    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setPosition(sf::Vector2f(center.x - size / 2, center.y - size / 2));
    shape.setFillColor(sf::Color(c.r, c.g, c.b));
    window_.draw(shape);
}

void Display::draw_line(Position start, Position end, Color c) {
    start.x *= scale;
    start.y *= scale;
    end.x *= scale;
    end.y *= scale;

    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(start.x, start.y), sf::Color(c.r, c.g, c.b)),
        sf::Vertex(sf::Vector2f(end.x, end.y), sf::Color(c.r, c.g, c.b))};

    window_.draw(line, 2, sf::Lines);
}

void Display::end_frame() {
    window_.display();
}
#else
constexpr int8_t CLK = 11;
constexpr int8_t OE = 9;
constexpr int8_t LAT = 10;
constexpr int8_t A = A0;
constexpr int8_t B = A1;
constexpr int8_t C = A2;
constexpr int8_t D = A3;

Display::Display() : window_(A, B, C, D, CLK, LAT, OE, true, 64) {
    window_.begin();
}

bool Display::begin_frame() {
    window_.fillScreen(window_.Color333(0, 0, 0));
    return true;
}

void Display::draw_square(Position center, Color c, uint8_t size) {
    window_.drawRect(center.x - size / 2,
                     center.y - size / 2,
                     size,
                     size,
                     window_.Color888(c.r, c.g, c.b));
}

void Display::draw_line(Position start, Position end, Color c) {
    window_.drawLine(start.x, start.y, end.x, end.y,
                     window_.Color888(c.r, c.g, c.b));
}

void Display::end_frame() {
    window_.swapBuffers(false);
}
#endif
