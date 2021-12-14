#include "saberduino/level.hpp"
#include "saberduino/saber.hpp"

Saber saber;
Level level;

void setup() {
  saber.init();
  level.init();
  level.start();
}

void loop() {
  level.update(saber.position());
}

#ifdef SABERDUINO_DESKTOP_COMPUTER
int main() {
    setup();
    while (true)
        loop();
}
#endif
