// The Wire library to use I2C.
#include <Wire.h>
// Adafruit libraries to write to the display Adafruit_GFX and Adafruit_SSD1306.
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Include Ticker library.
#include <Ticker.h>

// Width and Height in pixels.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define echoPin 2
#define trigPin 4
#define ledPin 5
#define btnPin 3

long duration;
int distance;
volatile int interruptsCounter;
volatile int btnInterruptCounter;
uint32_t timerValue = 2000;
bool test;
int buttonState;

void printDistance();
void btn_ISR();

Ticker timer(printDistance, (uint32_t)timerValue);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Not quite sure what this does? ! remember to ask Lærke or Lars.
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(btnPin), btn_ISR, CHANGE);

  // Start the Ticker.
  timer.start();
}

void loop() {
  // Update the Ticker
  timer.update();

  digitalWrite(ledPin, LOW);
  buttonState = digitalRead(btnPin);

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  if(true == test) {
  // Print to Serial Monitor
  Serial.print("Interrupts: ");
  Serial.print(interruptsCounter);
  Serial.println();
  Serial.print("Distance: ");
  Serial.print(distance, DEC);
  Serial.println();
  Serial.print("Timer: ");
  Serial.print(timerValue);
  Serial.println();
  Serial.print("Knap tryk: ");
  Serial.print(btnInterruptCounter);
  Serial.println();

  // Print to Display
  display.setCursor(0, 20);
  display.clearDisplay();

  // 1). Antal timer interrupts
  display.print("Interrupts: ");
  display.print(interruptsCounter);
  display.println();

  // 2). Sidste aflæste sensor værdi
  display.print("Distance: ");
  display.print(distance);
  display.println();

  // 3). Timeout værdi for Timer interrupt
  display.print("Timer: ");
  display.print(timerValue);
  display.println();

  // 4). Vis interrupts oprettet ved tryk på knap
  display.print("Knap tryk: ");
  display.print(btnInterruptCounter);

  digitalWrite(ledPin, HIGH);
  test = false;
  }

  delay(500);
  display.display();

  /*if(Serial.read() > 0) {
    Det viser sig at man ikke bare kan læse fra seriel port og få værdien som en int,
    Dvs. at man skal tage hver char i input, gemme i et char array og convertere til uint32_t med atoi().
    Det har jeg dog ikke fået til at virke..

    Jeg har forsøgt mig med følgende links:
    https://www.programmingelectronics.com/serial-read/
    https://www.tutorialspoint.com/arduino/arduino_strings.htm
    https://forum.arduino.cc/t/string-object-to-int/45437/2
    https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/tochararray/
    https://forum.arduino.cc/t/how-to-store-values-in-a-list-or-array/606820
    https://arduinogetstarted.com/faq/how-to-convert-string-variable-to-integer-in-arduino

    Hvis du kender måden eller ud af det blå lige kan forklare hvordan, vil jeg meget gerne se det Lars :-) 

    //timerValue = Serial.read();
  }*/
}

void printDistance() {
  interruptsCounter++;
  test = true;
}

void btn_ISR() {
  // Serial.println("button pressed");
  if(buttonState == HIGH) {
    btnInterruptCounter++;
  }
  test = true;
}