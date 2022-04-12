const int ledPin = 12;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  delay(200); 
  int inByte = Serial1.read();
  Serial.write(inByte);
}
