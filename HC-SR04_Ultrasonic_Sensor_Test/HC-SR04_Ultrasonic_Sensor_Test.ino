#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(OLED_RESET);

const int triggerPin = 10;
const int echoPin = 9;

long duration;
int distance;


void setup() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;

  Serial.print(" Distance: ");
  Serial.print(distance);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Distance: ");
  display.println(distance);
  if(distance > 9) {
     display.setCursor(26,16);
  }
  if(distance < 10) {
    display.setCursor(14,16);
  }
  if(distance > 99) {
    display.setCursor(36,16);
  }
  if(distance > 999)  {
    display.setCursor(48,16);
  }
  display.println("cm"); 
  display.display();
}
