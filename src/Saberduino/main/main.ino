#ifndef SABERDUINO_DESKTOP_COMPUTER

#include "saberduino/display.hpp"
#include "saberduino/level.hpp"
#include "saberduino/saber.hpp"

Saber saber;
Level level;
Display display;

Block default_blocks[10] = {
    Block{false, {8, 8}, 100},  Block{false, {8, 12}, 200},
    Block{false, {16, 8}, 300}, Block{false, {16, 12}, 400},
    Block{false, {8, 8}, 500},
};

void setup() {
    saber.init();
    level.init();
    level.load(default_blocks, 5);
    level.start();
}

void loop() {
    display.begin_frame();
    level.update(display, saber.position());
    display.end_frame();
}

int main() {
    setup();
    while (true)
        loop();
}

#endif
