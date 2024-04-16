#include <Wire.h>

#define LM75 0x4F

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // Temperaturdaten anfragen
  Wire.beginTransmission(LM75);
  Wire.endTransmission();
  
  // 2 Bytes von Temperaturdaten lesen
  Wire.requestFrom(LM75, 2);
  if(Wire.available() >= 2) { // Verfügbarkeit von 2 Bytes zum Auslesen prüfen
    byte c1 = Wire.read(); // erster byte
    byte c2 = Wire.read(); // zweiter byte
    
    // Beide Bytes in einen 16-bit integer kombinieren
    int16_t temp_raw = c1 * 256 + c2;
    
    // In Celsius konvertieren
    float temperatur = temp_raw / 256.0; 
    
    Serial.print("Temperature: ");
    Serial.print(temperatur);
    Serial.println(" °C");
  }
  
  delay(1000);
}
