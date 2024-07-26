#include <Arduino.h>

// Definiere Pins
#define POT_PIN PB3
#define LED_PIN PB0

void setup() {
  pinMode(POT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(POT_PIN);
  int brightness = map(sensorValue, 0, 1023, 0, 255);
  analogWrite(LED_PIN, brightness);
  delay(10); // kleine Verzögerung
}
