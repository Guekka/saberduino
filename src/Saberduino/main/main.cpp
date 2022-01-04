#ifdef SABERDUINO_DESKTOP_COMPUTER

#include "saberduino/display.hpp"
#include "saberduino/level.hpp"
#include "saberduino/saber.hpp"

Saber saber;
Level level;
Display display;

const Block default_blocks[10] = {
    Block{{4, 4}, 50},  Block{{8, 8}, 100}, Block{{11, 11}, 150},
    Block{{4, 4}, 200}, Block{{8, 8}, 250},
};

void setup() {
    saber.init();
    level.init();
    level.load(default_blocks);
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