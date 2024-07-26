// Definiere die Pin-Nummern 
#include <Arduino.h>

// Pin-Definitionen
const int ledRPin = 1;    // Rotanteil der RGB-LED
const int ledBPin = 2;    // Blauanteil der RGB-LED
const int ledGPin = 3;    // Grünanteil der RGB-LED
const int buzzerPin = 5;  // Buzzer
const int vibMotorPin = 6; // Vibrationsmotor
const int solarPin = 7;   // Solarzelle zur Spannungsüberwachung

// Timer-Konfiguration
const unsigned long workTime = 25UL * 60 * 1000;  // Arbeitszeit in Millisekunden (25 Minuten)
const unsigned long breakTime = 5UL * 60 * 1000;  // Pausenzeit in Millisekunden (5 Minuten)
const unsigned long signalDuration = 3000UL; // Dauer des Signalisierens (3 Sekunden)
const unsigned long vibInterval = 6000UL; // Vibration Intervall (6 Sekunden)
const unsigned long blinkInterval = 500UL; // Blink Intervall für die LED (0.5 Sekunden)
unsigned long previousMillis = 0;
unsigned long signalStartMillis = 0;
bool isWorking = true;
bool signaling = false;
bool vibrate = false;
unsigned long phaseStartMillis = 0;
unsigned long blinkMillis = 0;
bool ledState = false;

// Funktion zur Steuerung der LED-Farbe
void setLedColor(String color); // Vorwärtsdeklaration

// Initialisierung
void setup() {
  pinMode(ledRPin, OUTPUT);
  pinMode(ledBPin, OUTPUT);
  pinMode(ledGPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibMotorPin, OUTPUT);
  pinMode(solarPin, INPUT);
  
  // Initialisiere RGB-LED in aus Zustand
  digitalWrite(ledRPin, LOW);
  digitalWrite(ledBPin, LOW);
  digitalWrite(ledGPin, LOW);
  
  // Initialisiere Timer
  previousMillis = millis();
  phaseStartMillis = millis();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Lese die Spannung der Solarzelle aus
  int sensorValue = analogRead(solarPin);
  float voltage = sensorValue * (5.0 / 1023.0); // Umrechnung auf Spannung
  
  // Überprüfe, ob die Solarzelle genügend Spannung liefert
  if (voltage > 0.5) { // Anpassung des Schwellenwerts je nach Solarzelle
    // Timer basierter Code
    if (currentMillis - previousMillis >= (isWorking ? workTime : breakTime)) {
      previousMillis = currentMillis;
      
      // Wechsel zwischen Arbeits- und Pausenmodus
      isWorking = !isWorking;
      
      // Setze Signalisierung
      signaling = true;
      signalStartMillis = currentMillis;
      digitalWrite(buzzerPin, HIGH);
      vibrate = false; // Stoppe die Vibration während des Signalens
      phaseStartMillis = currentMillis;
      
      // Setze LEDs basierend auf dem neuen Modus
      setLedColor(isWorking ? "red" : "green");
    }

    // Überprüfe, ob die Signalisierung abgeschlossen ist
    if (signaling && (currentMillis - signalStartMillis >= signalDuration)) {
      signaling = false;
      digitalWrite(buzzerPin, LOW);
    }
    
    // Überprüfe, ob die Hälfte der Arbeitszeit vorbei ist
    if (isWorking && !signaling) {
      unsigned long elapsedTime = currentMillis - phaseStartMillis;
      
      if (elapsedTime >= workTime / 2 && !vibrate) {
        // Beginne Vibration zur Hälfte der Arbeitszeit
        vibrate = true;
        digitalWrite(vibMotorPin, HIGH);
        phaseStartMillis = currentMillis; // Reset für die Vibration
        blinkMillis = currentMillis; // Startzeit für das Blinken
      }
      
      // Beende Vibration nach der angegebenen Zeit
      if (vibrate && (currentMillis - phaseStartMillis >= vibInterval)) {
        digitalWrite(vibMotorPin, LOW);
        vibrate = false;
      }
      
      // Blinken der LED während der Vibration
      if (vibrate) {
        if (currentMillis - blinkMillis >= blinkInterval) {
          blinkMillis = currentMillis;
          ledState = !ledState;
          digitalWrite(ledBPin, ledState ? HIGH : LOW);
        }
      }
    }
    
    // Setze die LED auf gelb, wenn signalisierend
    if (signaling) {
      setLedColor("yellow");
    }
    
  } else {
    // Solarzelle liefert nicht genügend Spannung: Alles aus
    digitalWrite(ledRPin, LOW);
    digitalWrite(ledBPin, LOW);
    digitalWrite(ledGPin, LOW);
    digitalWrite(buzzerPin, LOW);
    digitalWrite(vibMotorPin, LOW);
  }
}

// Funktion zur Steuerung der LED-Farbe
void setLedColor(String color) {
  if (color == "red") {
    digitalWrite(ledRPin, HIGH);
    digitalWrite(ledGPin, LOW);
    digitalWrite(ledBPin, LOW);
  } else if (color == "green") {
    digitalWrite(ledRPin, LOW);
    digitalWrite(ledGPin, HIGH);
    digitalWrite(ledBPin, LOW);
  } else if (color == "yellow") {
    digitalWrite(ledRPin, HIGH);
    digitalWrite(ledGPin, HIGH);
    digitalWrite(ledBPin, LOW);
  } else if (color == "blue") {
    digitalWrite(ledRPin, LOW);
    digitalWrite(ledGPin, LOW);
    digitalWrite(ledBPin, HIGH);
  }
}
