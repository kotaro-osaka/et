#include <Wire.h>

#define TARGET_1 0x01 // Potentiometer
#define TARGET_2 0x02 // RGB LED

void setup() {
    Serial.begin(9600);
    Wire.begin();
}

void loop() {
    // RGB Werte anfordern
    Wire.requestFrom(TARGET_1, 3)

    // Antwort auslesen (jeweils 1 byte)
    int r = Wire.read();
    int g = Wire.read();
    int b = Wire.read();

    // RGB Werte an TARGET_2 senden
    Wire.beginTransmission(TARGET_2);
    Wire.write(r);
    Wire.write(g);
    Wire.write(b);
    Wire.endTransmission();

    // Aktualisiert RGB LED alle 100ms
    delay(100);
}

void test {
    
}