#include <Wire.h>

#define TARGET_1 0x01 // Potentiometer Arduino
#define TARGET_2 0x02 // RGB LED Arduino

// Zwischenlager fuer RGB Werte
int r = 0;
int g = 0;
int b = 0;


void setup() {
    Serial.begin(9600);
    Wire.begin(); // I2C als master initialisieren
}


void loop() {
    // RGB Werte von TARGET_2 anfragen
    readT1();

    // RGB Werte an TARGET_2 senden
    writeT2();

    // Versucht LED alle 100ms zu aktualisieren
    delay(100);
}


void readT1() {
    // RGB Werte anfordern; stopMsg=true
    Wire.requestFrom(TARGET_1, 3, true);

    // Sicherstellen, dass Bytes zum Abruf verfügbar sind
    if (Wire.available()) {
        // Antwort auslesen (jeweils 1 byte)
        r = Wire.read();
        g = Wire.read();
        b = Wire.read();

        printRGB();
    } else {
        Serial.println("Error: Keine Daten von Target_1 verfuegbar");
    }
}


void writeT2() {
    Wire.beginTransmission(TARGET_2);
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();
}


// Hilfsfunktionen

// Ausgabe aktueller RGB Werte
void printRGB() {
    Serial.println("Aktuelle RGB Werte");
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
}


// LED manuell aktualisieren
void updateLED() {
    Wire.beginTransmission(TARGET_2);
    Wire.write("update");
    Wire.endTransmission(TARGET_2);
}