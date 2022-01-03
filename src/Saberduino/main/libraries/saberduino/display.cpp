#include "display.hpp"

Display::Display()
    : window_(sf::VideoMode(len * scale, len * scale), "Saberduino") {}

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

void Display::draw_pix(Position pos, uint8_t r, uint8_t g, uint8_t b) {
    sf::RectangleShape shape(sf::Vector2f(scale, scale));
    shape.setPosition(sf::Vector2f(scale * pos.x, scale * pos.y));
    shape.setFillColor(sf::Color(r, g, b));
    window_.draw(shape);
}

void Display::end_frame() {
    window_.display();
}
