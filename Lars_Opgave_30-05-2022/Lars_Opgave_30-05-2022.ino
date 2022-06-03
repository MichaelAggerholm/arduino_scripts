int incomingByte = 0;

enum read_states{
  Modtag_Adresse, 
  Modtag_Bit_Position_I_Adresse, 
  Modtag_Bit_Position_Vaerdi
};

enum read_states state;

int ledPin = 51;

void setup() {
  pinMode(ledPin, OUTPUT); 
  state = Modtag_Adresse;
  Serial.begin(9600);
  delay(500);
}

void loop() {
  digitalWrite(ledPin, LOW);

  if(state == Modtag_Adresse) {
    // Brug serial monitor message til manuelt at sende en seriel værdi..
    if(Serial.available() > 0)  {
      char input_array = Serial.read();
      incomingByte = input_array;
      Serial.print(input_array);
      //Serial.println(incomingByte, DEC);
      state = Modtag_Bit_Position_I_Adresse;
    }
  }

  else if(state == Modtag_Bit_Position_I_Adresse) {
    // Serial.println("Modtag_Bit_Position_I_Adresse");
    if(incomingByte > 0 && incomingByte < 8) {
      state = Modtag_Bit_Position_Vaerdi;
    } else {
      state = Modtag_Adresse;
    }
  }

  else if(state == Modtag_Bit_Position_Vaerdi) {
    // hvordan skal vi definere hvad der er 0 og hvad der er 1, LARS?!
    // Modtag_Bit_Position_Vaerdi
    if(incomingByte > 0 && incomingByte < 5) {
      // 0 = Bit position LOW
      digitalWrite(ledPin, HIGH);
    } else {
      // 1 = Bit position HIGH
      digitalWrite(ledPin, LOW);
    }
  }
}