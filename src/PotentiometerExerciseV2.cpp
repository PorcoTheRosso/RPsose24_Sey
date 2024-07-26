#include <Arduino.h>

// Definiere Pins
#define POT_PIN PB3
#define BUZZER_PIN PB0

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(POT_PIN);
  int frequency = map(sensorValue, 0, 1023, 100, 1000);
  tone(BUZZER_PIN, frequency);
  delay(10); // kleine Verzögerung
}
