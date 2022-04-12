int led_pin = A1;
int button_pin = A4;
void setup() { 
  pinMode(led_pin, OUTPUT); 
  pinMode(button_pin, INPUT); 
}
void loop() { 
  digitalWrite(led_pin, LOW);
  
  int button_state = digitalRead(button_pin);
  if (button_state == HIGH) {
    digitalWrite(led_pin, HIGH);
  }else {   
    digitalWrite(led_pin, LOW);
  }
}
