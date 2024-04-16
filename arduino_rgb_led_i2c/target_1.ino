// Potentiometer
#include <Wire.h>

const int pinR = A0;
const int pinG = A1;
const int pinB = A2;

int r = 0;
int g = 0;
int b = 0;

void setup() {
    Serial.begin(9600);
    Wire.onRequest(rgbSenden());
}

void loop() {
    // Potentiometer Werte auslesen (Werte sind im Bereich 0-1023)
    int r = analogRead(pinR);
    int g = analogRead(pinG);
    int b = analogRead(pinB);

    // Werte ausgeben
    Serial.print("R: ");
    Serial.println(r);
    Serial.print("G ");
    Serial.println(g);
    Serial.print("B ");
    Serial.println(b);
}

// RGB Werte an Master senden
void rgbSenden() {
    Serial.println("Datenuebertragung an Master initialisiert");

    // `/ 4` um Bereich von 0-1023 auf 0-254 zu begrenzen (LED akzeptiert Werte im Bereich 0-254)
    Wire.write(r / 4);
    Wire.write(g / 4);
    Wire.write(b / 4);

    Serial.println("Datenuebertragung an Master abgeschlossen");
}