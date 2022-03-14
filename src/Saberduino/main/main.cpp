#ifdef SABERDUINO_DESKTOP_COMPUTER

#include "saberduino/display.hpp"
#include "saberduino/level.hpp"
#include "saberduino/saber.hpp"
#include "saberduino/levels.hpp"

Saber saber;
Level level(popstar_1h_hard, popstar_1h_hard_len);
Display display;

void setup() {
    saber.init();
    display.init();
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
