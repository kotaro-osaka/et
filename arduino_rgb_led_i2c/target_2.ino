// RGB LED
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    Wire.onRequest(updateLed());
}

void loop() {

}

void updateLed(r, g, b) {
    analogWrite()
}



#include <Wire.h>

#define TARGET_ADDRESS 0x02 // Address of the target Arduino

void receiveEvent(int numBytes) {
  while (Wire.available() > 0) { // Check if data is available to read
    byte data = Wire.read(); // Read the received data byte
    Serial.print(data); // Output the received data (you might change this based on your requirements)
  }
}
