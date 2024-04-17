#include <Wire.h>

// Potenziometer Pins
const int pinR = A0;
const int pinG = A1;
const int pinB = A2;

// Werte von Potenziometern
int r = 0;
int g = 0;
int b = 0;


void setup() {
    Serial.begin(9600);

    pinMode(pinR, INPUT);
    pinMode(pinG, INPUT);
    pinMode(pinB, INPUT);

    Wire.begin(0x01); // I2C als Target initialisieren
    Wire.onRequest(rgbSenden);
}


// Aktiv Potenziometer Werte auslesen, speichern (und ausgeben)
void loop() {
    // `/ 4` um Wertebereich von 0-1023 auf 0-254 zu begrenzen
    r = analogRead(pinR) / 4;
    g = analogRead(pinG) / 4;
    b = analogRead(pinB) / 4;

    printRGB();
}


// RGB Werte an Master senden
void rgbSenden() {
    Serial.println("Datenuebertragung an Master initialisiert");

    // `/ 4` um Bereich von 0-1023 auf 0-254 zu begrenzen (LED akzeptiert Werte im Bereich 0-254)
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);

    Serial.println("Datenuebertragung an Master abgeschlossen");
}


// Hilfsfunktion

// Ausgabe aktueller RGB Werte
void printRGB() {
    Serial.println("Aktuelle RGB Werte");
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
}