int redPin = 11;
int greenPin = 10;
int bluePin = 9;

bool randomColor = false;

void setup() {
	pinMode(redPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
	pinMode(greenPin, OUTPUT);
  randomSeed(analogRead(0));
}

void setRandomColor() {
  sendColor(random(256), random(256), random(256));
}

void sendColor(int red, int blue, int green) {
	analogWrite(redPin, red);
	analogWrite(bluePin, green);
	analogWrite(greenPin, blue);
}

void loop() {
  setRandomColor();
  delay(3000);
}