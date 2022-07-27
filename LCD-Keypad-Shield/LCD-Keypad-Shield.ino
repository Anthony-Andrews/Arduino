#include <LiquidCrystal.h>
#include <BasicStepperDriver.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 

#define DIR 44
#define STEP 46

#define MOTOR_STEPS 200
#define RPM 120
#define MICROSTEPS 2

BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP);

int speed = 0;
int step = 0;
int ENABLE_PIN = true;
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

void setup() {
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Stepper Tester:");
 lcd.setCursor(0,1);
 lcd.print("Speed:");
 Serial.begin(9600);

 pinMode(53, OUTPUT);
 pinMode(52, OUTPUT);
 pinMode(46, OUTPUT);
 pinMode(44, OUTPUT);
 digitalWrite(53, HIGH);
 digitalWrite(52, HIGH);
 delay(100);
 digitalWrite(53, LOW);
 digitalWrite(52, LOW);
 stepper.begin(RPM, MICROSTEPS);

}
void loop() {
 int x;
 x = analogRead (0);
 if (x < 60) {
  ENABLE_PIN = !ENABLE_PIN;
  delay(200);
 }
 else if (x < 200) {
   if (speed < 100) {
     delay(200);
     speed = speed + 10;
   }
 }
 else if (x < 400){
   if (speed > -100) {
     delay(200);
     speed = speed - 10;
   }
 }
 else if (x < 600){
  speed = 0;
 }
 else if (x < 800){
 }

 lcd.setCursor(7,1);
 lcd.print (speed);
 lcd.print ("%   ");

 if (speed != 0) {
  stepper.rotate(speed/2);
 }
  digitalWrite(53, ENABLE_PIN);
  digitalWrite(52, ENABLE_PIN);
  delay(speed / 10);
}
