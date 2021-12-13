#include "saberduino/display.hpp"
#include "saberduino/level.hpp"
#include "saberduino/saber.hpp"

Saber saber;
Level level;
Display display;

void setup() {
    saber.init();
    level.init();
    level.start();
}

void loop() {
    display.begin_frame();
    for (uint8_t i = 4; i < display.len - 4; ++i)
        for (uint8_t j = 4; j < display.len - 4; ++j) {
            display.draw_pix(Position{i, j}, 100, 100, 100);
        }
    display.end_frame();
    // level.update(saber.position());
}

int main() {
    setup();
    while (true)
        loop();
}
