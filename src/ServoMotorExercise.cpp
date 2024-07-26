#include <Arduino.h>
#include <TinyServo.h> // Verwenden Sie die angepasste Servo Bibliothek für ATtiny

// Definiere Pins
#define SERVO_PIN PB1

TinyServo myServo;

void setup() {
  myServo.attach(SERVO_PIN);
}

void loop() {
  myServo.write(0);  // Position 1
  delay(1000);       // 1 Sekunde warten
  myServo.write(180); // Position 2
  delay(1000);       // 1 Sekunde warten
}
