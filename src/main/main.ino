#include "saber.hpp"
#include "level.hpp"

Saber saber;
Level level;

void setup() {
  Serial.begin(9600);
  saber.init();
  level.init();
  level.start();
}

void loop() {
  level.update(saber.position());
  delay(1000);
}
