#include <Arduino.h>

// Definiere Pins
#define BUZZER_PIN PB0

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  tone(BUZZER_PIN, 1000); // 1000 Hz Ton
  delay(500);             // 500 ms
  noTone(BUZZER_PIN);
  delay(500);             // 500 ms
}
