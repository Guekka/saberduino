void setup() {
  Serial.begin(38400);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  Serial2.begin(38400);
  delay(500);
}


void loop() {
  while (Serial2.available()) {
    Serial.print(char(Serial2.read()));
  }
  while (Serial.available()) {
    char r = Serial.read();
    Serial2.write(r);
  }
}
