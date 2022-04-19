// Guide jeg har benyttet: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/

// The Wire library to use I2C.
#include <Wire.h>
// Adafruit libraries to write to the display Adafruit_GFX and Adafruit_SSD1306.
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Font
#include <Fonts/FreeMonoBoldOblique12pt7b.h>

// Width and Height in pixels.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define echoPin 2
#define trigPin 3

long duration;
int distance;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // initialize the Serial Monitor at a baud raute of 115200 for debugging purposes.
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Not quite sure what this does? ! remember to ask Lærke or Lars.
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  //display.setFont(&FreeMonoBoldOblique12pt7b);
  // To print static text as test.
  //display.println("Hej Jack!");
  //display.display(); 

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
}

void loop() {
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
  // Displays the distance on the Serial Monitor
  
  display.setCursor(0, 10);
  display.clearDisplay();

  //Serial.print("Distance: ");
  display.print("cm: ");
  display.print(distance);
  display.display();
}
