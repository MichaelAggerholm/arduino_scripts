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
#define trigPin 3
#define ledPin 4

long duration;
int distance;
int interruptsCounter;
uint32_t timerValue = 2000;
volatile bool test;

void printDistance();

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
  Serial.begin(9600);

  // Start the Ticker.
  timer.start();
}

void loop() {
  // Update the Ticker
  timer.update();

  digitalWrite(ledPin, LOW);

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

  // Print to Display
  display.setCursor(0, 5);
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

  display.display();

  digitalWrite(ledPin, HIGH);
  delay(500);
  test = false;
  }
}

void printDistance() {
  interruptsCounter++;
  test = true;
}
