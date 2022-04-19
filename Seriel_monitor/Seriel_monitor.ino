const int button_pin = 6;
const int led_pin = 3;
int value = 1;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(button_pin, INPUT);
  pinMode(led_pin, OUTPUT);
}

void loop() {
  digitalWrite(led_pin, LOW);
  
  // Receive
  /*while (Serial1.available() > 0) {
    //delay(100);
    int inByte = Serial1.parseInt();
    Serial.println(inByte, DEC);
  }*/

  // Send
  int button_state = digitalRead(button_pin);
  Serial.println(button_state);
  if (button_state == HIGH) {
    digitalWrite(led_pin, HIGH);
    value = constrain(value, 0, 255);
    Serial1.print(value, DEC);
  }
}
