// ATtiny Blink
// LED an Pin 0

#include <Arduino.h>
void setup() {
  // Setze Pin 0 als Ausgang
  pinMode(0, OUTPUT);
}

void loop() {
  // LED einschalten
  digitalWrite(0, HIGH);
  delay(1000); // Warte 1 Sekunde
  // LED ausschalten
  digitalWrite(0, LOW);
  delay(1000); // Warte 1 Sekunde
}
