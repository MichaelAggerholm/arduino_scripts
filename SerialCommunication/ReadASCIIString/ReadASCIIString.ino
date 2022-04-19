const int bluePin = 6;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // make the pins outputs:
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    int blue = Serial.parseInt();
    blue = constrain(blue, 0, 255);
    analogWrite(bluePin, blue);
    Serial.println(blue, DEC);
  }
}
