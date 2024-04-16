int SDI = 3; // Serial Data Input
int SCLK = 5; // Serial Clock - Signal, das Datentransfer synchronisiert
int LOAD = 6; // Signal, das SDI Daten an Displayspeicher sendet

int userInput = -1; // Um sicherzustellen, dass es zunaechst keiner gueltigen Eingabe entspricht

// Low-Aktiv - 10 Ziffern mit jeweils 16 Bits
int zahlen[10][16] = { 
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 }, // 0
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1 }, // 1
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0 }, // 2
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0 }, // 3
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1 }, // 4
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0 }, // 5
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0 }, // 6
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0 }, // 7
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0 }  // 9
};

void setup() {
  Serial.begin(9600); // Start der seriellen Kommunikation mit Baudrate 9600
  pinMode(SDI, OUTPUT);
  pinMode(SCLK, OUTPUT);
  pinMode(LOAD, OUTPUT);
}

void sendToDisplay(int ziffer) { // * = Array-Parameter
  digitalWrite(LOAD, LOW); // LOAD auf LOW, um Latch-Vorgang zu aktivieren - Speichermodus
  for (int i = 0; i < 16; i++) { // Schleife fuer 16 Bit Muster
    digitalWrite(SCLK, LOW);
    digitalWrite(SDI, zahlen[ziffer][i]);
    Serial.print(zahlen[ziffer][i]);
    digitalWrite(SCLK, HIGH);
  }
  Serial.println("\n");
  digitalWrite(LOAD, HIGH);
}

void loop() {
  if (Serial.available() > 0) {
    userInput = Serial.read() - '0'; // ASCII zu integer
    if (userInput >= 0 && userInput <= 9) {
      sendToDisplay(userInput);
    } else {
      Serial.println("Gebe eine Zahl zwischen 0 und 9 ein.");
    }
  }
}