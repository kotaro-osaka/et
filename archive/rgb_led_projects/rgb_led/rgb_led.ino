int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup() {
  Serial.begin(9600);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void userCustomColor() {
  int red = Serial.parseInt();
  int blue = Serial.parseInt();
  int green = Serial.parseInt();

  // Werte zwischen 0-255
  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);

  if (red != 0 || green != 0 || blue != 0) {
    sendColor(red, blue, green);
  }
}

void sendColor(int red, int blue, int green) {
	analogWrite(redPin, red);
	analogWrite(bluePin, green);
	analogWrite(greenPin, blue);
}

void loop() {
  userCustomColor();
  delay(3000);
}