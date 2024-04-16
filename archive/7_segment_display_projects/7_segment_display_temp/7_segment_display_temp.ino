int SDI = 3;
int SCLK = 5;
int LOAD = 6;

double sensorValue = 0;
double sensorU = 0;
double sensorR = 0;
double tempK = 0;
double tempC = 0;
double analogPin = A0;

int temp = 0;
int einer = 0;
int zehner = 0;

// Low-Aktiv - 10 Ziffern mit jeweils 8 Bits
int ziffern[12][8] = { 
  { 1, 1, 0, 0, 0, 0, 0, 0 }, // 0
  { 1, 1, 1, 1, 1, 0, 0, 1 }, // 1
  { 1, 0, 1, 0, 0, 1, 0, 0 }, // 2
  { 1, 0, 1, 1, 0, 0, 0, 0 }, // 3
  { 1, 0, 0, 1, 1, 0, 0, 1 }, // 4
  { 1, 0, 0, 1, 0, 0, 1, 0 }, // 5
  { 1, 0, 0, 0, 0, 0, 1, 0 }, // 6
  { 1, 1, 1, 1, 1, 0, 0, 0 }, // 7
  { 1, 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 1, 0, 0, 1, 0, 0, 0, 0 }, // 9
  { 1, 0, 1, 1, 1, 1, 1, 1 }, // -
  { 1, 1, 1, 1, 1, 1, 1, 1 }  // /
};

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(LOAD, OUTPUT);
}

void calcTemp() {
  sensorValue = analogRead(analogPin);
  sensorU = (5 * sensorValue) / 1023; // Spannung des Sensors
  sensorR = (sensorValue * 10000) / (1023 - sensorValue); // Berechnet den Widerstand des Sensors
  // temp in Kelvin
  tempK = pow(3.354016 *
    pow(10, -3) + 2.569850 *
    pow(10, -4) *
    log(sensorR / 10000) +
    2.62013 * pow(10, -12) *
    pow(log(sensorR / 10000), 2) +
    6.38309 * pow(10, -15) *
    pow(log(sensorR / 10000), 3), -1);
  tempC = tempK - 273.15; // Konvertiert die Temperatur in Celsius
  temp = round(tempC);
  if (temp < 0 && temp > -10) {
    negTemp();
  } else if (-9 > temp) {
    negLowerTemp();
  } else {
    posTemp();
  }
}

void posTemp() {
  digitalWrite(LOAD, LOW);
  // einer
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[temp % 10][i]);
    digitalWrite(SCLK, HIGH);
  }
  // zehner
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[temp / 10][i]);
    digitalWrite(SCLK, HIGH);
  }
  digitalWrite(LOAD, HIGH);
}

void negTemp() {
  digitalWrite(LOAD, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[temp * (-1)][i]);
    digitalWrite(SCLK, HIGH);
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[10][i]);
    digitalWrite(SCLK, HIGH);
  }
  digitalWrite(LOAD, HIGH);
}

void negLowerTemp() {
  digitalWrite(LOAD, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[11][i]);
    digitalWrite(SCLK, HIGH);
  }
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[10][i]);
    digitalWrite(SCLK, HIGH);
  }
  digitalWrite(LOAD, HIGH);
  delay(250);
  digitalWrite(LOAD, LOW);
  // einer
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[(temp * (-1)) % 10][i]);
    digitalWrite(SCLK, HIGH);
  }
  // zehner
  for (int i = 0; i < 8; i++) {
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, ziffern[(temp * (-1)) / 10][i]);
    digitalWrite(SCLK, HIGH);
  }
  digitalWrite(LOAD, HIGH);
  delay(500);
}

void loop() {
  calcTemp();
}