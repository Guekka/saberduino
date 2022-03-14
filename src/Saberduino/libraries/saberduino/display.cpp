#include "display.hpp"
#include "printer.hpp"

Position Display::from_placing(Position pos)
{
    // We expect x in [0, 3] and y in [0, 2]
    pos.x *= (width * scale) / 4;
    pos.y *= (height * scale) / 3;
    return pos;
}

#ifdef SABERDUINO_DESKTOP_COMPUTER
Display::Display()
    : window_(sf::VideoMode(width * scale, height * scale), "Saberduino") {}

void Display::init() {}
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
    shape.setOutlineColor(sf::Color(c.r, c.g, c.b));
    shape.setOutlineThickness(3);
    window_.draw(shape);
}

void Display::fill_rect(Position topleft, Color c, uint8_t w, uint8_t h) {
    topleft.x *= scale;
    topleft.y *= scale;
    w *= scale;
    h *= scale;

    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setPosition(sf::Vector2f(topleft.x, topleft.y));
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

void Display::draw_cube(Position topleft,
                        uint8_t size,
                        Color frontc,
                        Color backc) {
    // We expect x in [0, 3] and y in [0, 2]
    topleft.x *= (width * scale) / 4;
    topleft.y *= (height * scale) / 3;

    auto x  = topleft.x;
    auto y = topleft.y;
    auto x2 = static_cast<uint8_t>(x + 2);
    auto y2 = static_cast<uint8_t>(y - 2);

    // Back square
    fill_rect({x2, y2}, backc, size, size);
    // Front square (overwrites back)
    fill_rect({x, y}, frontc, size, size);

    // Rest
    sf::ConvexShape topface;
    topface.setPointCount(4);
    topface.setPoint(
        0, {static_cast<float>(x * scale), static_cast<float>(y * scale)});
    topface.setPoint(
        1, {static_cast<float>(x * scale), static_cast<float>(y * scale)});
    topface.setPoint(
        2, {static_cast<float>(x * scale), static_cast<float>(y * scale)});
    topface.setPoint(3, {static_cast<float>(x), static_cast<float>(y)});

    draw_line({static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y - 1)},
              {x2, y2}, backc);
    /*
    draw_line(
        {static_cast<uint8_t>(x + size), static_cast<uint8_t>(y + size - 2)},
        {static_cast<uint8_t>(x2 + size - 1),
         static_cast<uint8_t>(y2 + size - 1)},
        backc);
    */
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

Display::Display() : window_(A, B, C, D, CLK, LAT, OE, true, 64) {}

void Display::init()
{
    window_.begin();
}

bool Display::begin_frame() {
    window_.fillScreen(window_.Color333(0, 0, 0));
    return true;
}

void Display::draw_square(Position center, Color c, uint8_t size) {
    window_.drawRect(center.x - size / 2, center.y - size / 2, size, size,
                     window_.Color888(c.r, c.g, c.b));
}

void Display::fill_rect(Position topleft, Color c, uint8_t w, uint8_t h) {
    window_.fillRect(topleft.x, topleft.y, w, h,
                     window_.Color888(c.r, c.g, c.b));
}

void Display::draw_line(Position start, Position end, Color c) {
    window_.drawLine(start.x, start.y, end.x, end.y,
                     window_.Color888(c.r, c.g, c.b));
}

void Display::end_frame() {
    window_.swapBuffers(false);
}

void Display::draw_cube(Position topleft, uint8_t size, Color frontc, Color backc)
{
    // We expect x in [0, 3] and y in [0, 2]
    topleft.x *= (width * scale) / 4;
    topleft.y *= (height * scale) / 3;

    auto x  = topleft.x + 2;
    auto y  = topleft.y + 2;
    auto x2 = static_cast<uint8_t>(x + 2);
    auto y2 = static_cast<uint8_t>(y - 2);

    // Back square
    fill_rect({x2, y2}, backc, size, size);
    // Front square (overwrites back)
    fill_rect({x, y}, frontc, size, size);

    // Link both
    draw_line({static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y - 1)},
              {x2, y2}, backc);
    draw_line(
        {static_cast<uint8_t>(x + size), static_cast<uint8_t>(y + size - 2)},
        {static_cast<uint8_t>(x2 + size - 1),
         static_cast<uint8_t>(y2 + size - 1)},
        backc);
}

#endif
