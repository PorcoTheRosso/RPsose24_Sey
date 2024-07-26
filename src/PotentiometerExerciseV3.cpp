#include <Arduino.h>
#include <TinyServo.h> // Verwenden Sie die angepasste Servo Bibliothek für ATtiny

// Definiere Pins
#define POT_PIN PB3
#define SERVO_PIN PB1

TinyServo myServo;

void setup() {
  pinMode(POT_PIN, INPUT);
  myServo.attach(SERVO_PIN);
}

void loop() {
  int sensorValue = analogRead(POT_PIN);
  int angle = map(sensorValue, 0, 1023, 0, 180);
  myServo.write(angle);
  delay(10); // kleine Verzögerung
}
