# RGB LED Steuerung mit Potenziometern über I2C
Datum

Elektrotechnik CI3M1

> Gruppe: Sophia, Kotaro, Kevin, Marius

<img src="./schaltplan.png" width="750">


## Inhalt
1. Hardware
2. Schaltplan Aufbau
3. Code
4. Quellen


## Hardware
Für das Projekt wird folgende Hardware benötigt:
- $3\times$ Arduino Uno
- $3\times$ Potenziometer
- $2\times$ $1.5kΩ$ Widerstand 
- $3\times$ $1kΩ$ Widerstand
- $1\times$ RGB LED
- Verbindungskabel


## Schaltplan Aufbau
1. `SCL` & `SDA` aller Arduinos werden miteinander verbunden um Kommunikation zwischen Master und Targets über I2C zu ermöglichen
2. `SCL` & `SDA` werden mit `5V` von Master über Pull-Up-Widerstände (`1.5kΩ`) versorgt, um Signalleitungen während Inaktivität, auf definierten Pegel zu ziehen
3. Ground (GND) aller Arduinos werden miteinander verbunden, um konstantes, einheitliches Bezugspotenzial für Signale zu schaffen (*Sorgt für klare Interpretation der Daten*)

### Target 1 (Potenziometer Input)
1. Potenziometer werden mit `5V` versorgt und mit Ground (GND) verbunden, um einen geschlossenen Stromkreis zu bilden
2. Variable Spannungen der jeweiligen Potenziometer werden über Pins `A0`, `A1`, `A2` ausgelesen

### Target 2 (RGB LED Output)
1. RGB LED Beine mit PWM-Pins `~3`, `~5`, `~6` über `1.5kΩ` Widerstände verbinden, um Helligkeit jeweiliger Farben (rot, grün, blau) individuell anpassen und blenden zu können
2. RGB LED Kathode mit synchronisiertem Ground (GND) verbinden


## Code

### Master
```cpp
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
```

### Target 1 (Potenziometer)
```cpp
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
```

### Target 2 (RGB LED)
```cpp
#include <Wire.h>

// LED Pins
const int pinR = 6;
const int pinG = 3;
const int pinB = 5;

// RGB Werte fuer LED
int r = 0;
int g = 0;
int b = 0;


void setup() {
    Serial.begin(9600);

    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);

    Wire.begin(0x02); // I2C als Target initialisieren
    Wire.onReceive(updateRGB); // LED mit gesendeten Werten aktualisieren
}


void loop() {
    // Reagiert nur auf Anfragen mit `Wire.onReceive` / `Wire.onRequest()`
}


// Aktualisiert RGB Werte
void updateRGB() {
    Serial.println("Update Anfrage von Master erhalten");
    if (Wire.available()) {
        // Werte auslesen (jeweils 1 byte)
        r = Wire.read();
        g = Wire.read();
        b = Wire.read();
        Serial.println("Werte erfolgreich ausgelesen");

        printRGB();
    } else {
        Serial.println("Error: Keine Daten von Master verfuegbar");
    }

    updateLED();
}


// LED Farbe an aktuelle RGB Werte anpassen
void updateLED() {
    digitalWrite(pinR, r);
    digitalWrite(pinG, g);
    digitalWrite(pinB, b);
}


// Hilfsfunktionen

// Ausgabe aktueller RGB Werte
void printRGB() {
    Serial.println("Aktuelle RGB Werte");
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
}
```


## Quellen
- [Wire Library](https://www.arduino.cc/reference/en/language/functions/communication/wire/)