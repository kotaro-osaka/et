int SDI = 3;
int SCLK = 5;
int LOAD = 6;

int zahl[16];

// Low-Aktiv - 10 Ziffern mit jeweils 8 Bits
int ziffern[10][8] = { 
  { 1, 1, 0, 0, 0, 0, 0, 0 }, // 0
  { 1, 1, 1, 1, 1, 0, 0, 1 }, // 1
  { 1, 0, 1, 0, 0, 1, 0, 0 }, // 2
  { 1, 0, 1, 1, 0, 0, 0, 0 }, // 3
  { 1, 0, 0, 1, 1, 0, 0, 1 }, // 4
  { 1, 0, 0, 1, 0, 0, 1, 0 }, // 5
  { 1, 0, 0, 0, 0, 0, 1, 0 }, // 6
  { 1, 1, 1, 1, 1, 0, 0, 0 }, // 7
  { 1, 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 1, 0, 0, 1, 0, 0, 0, 0 }  // 9
};

void setup() {
  pinMode(SDI, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(LOAD, OUTPUT);
}

void sendToDisplay() {
  digitalWrite(LOAD, LOW); // LOAD auf LOW, um Latch-Vorgang zu aktivieren - Speichermodus
  for (int i = 0; i < 16; i++) { // Schleife fuer 16 Bit Muster
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, zahl[i]);
    Serial.print(zahl[i]);
    digitalWrite(SCLK, HIGH);
  }
  Serial.println("\n");
  digitalWrite(LOAD, HIGH);
}

void to16Bits(int nummer) {
  if (nummer >= 0 && nummer <= 99) {    
    for (int i = 0; i < 8; i++) {
      zahl[i] = ziffern[nummer / 10][i];
      zahl[i + 8] = ziffern[nummer % 10][i];
    }
    sendToDisplay();
  }
}

void loop() {
  for(int i = 0; i <= 99; i++) {
    to16Bits(i);
    delay(1000);
  }
}