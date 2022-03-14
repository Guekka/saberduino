#ifndef SABERDUINO_DESKTOP_COMPUTER

#include "display.hpp"
#include "level.hpp"
#include "saber.hpp"
#include "levels.hpp"
#include "music.hpp"

Saber saber;
Level level(popstar_1h_hard, popstar_1h_hard_len);
Display display;
Music music;

void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);
  Serial.println("hey");

  saber.init();
  display.init();
  music.init();

  while (true) {
    if (Serial2.available() && Serial2.read() == 'S')
      break;
  }

  music.play(4);
  level.start();
}

void loop() {
  display.begin_frame();
  level.update(display, saber.position());
  display.end_frame();
}

#endif
