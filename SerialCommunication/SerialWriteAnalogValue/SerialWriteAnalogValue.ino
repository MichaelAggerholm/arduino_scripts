const int analogPin = A0;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(analogPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  value = analogRead(analogPin);
  value = constrain(value, 0, 255);
  Serial.println(value, DEC);
  delay(800);
}
