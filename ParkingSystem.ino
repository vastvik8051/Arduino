#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SENSOR_1_PIN 2 // Pin for first IR sensor (INT0)
#define SENSOR_2_PIN 3 // Pin for second IR sensor (INT1)
volatile unsigned long timeSensor1 = 0;
volatile unsigned long timeSensor2 = 0;
volatile bool sensor1Triggered = false;
volatile bool sensor2Triggered = false;
const float distanceBetweenSensors = 0.1; // Distance between sensors in meters
float speed = 0; // Speed in meters per second (m/s)

void setup() 
{
 // Initialize the LCD
 lcd.init();
 lcd.backlight();
 lcd.setCursor(0, 0);
 lcd.print("Speed Gun");
 delay(2000); // Show the title for 2 seconds
 lcd.clear();
 pinMode(SENSOR_1_PIN, INPUT);
 pinMode(SENSOR_2_PIN, INPUT);
 
 attachInterrupt(digitalPinToInterrupt(SENSOR_1_PIN), sensor1ISR, RISING);
 attachInterrupt(digitalPinToInterrupt(SENSOR_2_PIN), sensor2ISR, RISING);
}

void loop() {
 if (sensor1Triggered && sensor2Triggered) {
   sensor1Triggered = false;
   sensor2Triggered = false;
   unsigned long timeDifference = abs(timeSensor2 - timeSensor1); // Time in microseconds
   lcd.clear();
   if (timeDifference > 0) {
     speed = distanceBetweenSensors / (timeDifference / 1000000.0); // Convert µs to seconds
     lcd.setCursor(0, 0);
     lcd.print("Speed:");
     lcd.setCursor(0, 1);
     lcd.print(speed, 2); // Display speed with 2 decimal places
     lcd.print(" m/s");
   } else {
     lcd.setCursor(0, 0);
     lcd.print("Invalid Reading!");
   }
 }
}

void sensor1ISR() {
 if (!sensor1Triggered) { 
   timeSensor1 = micros();
   sensor1Triggered = true;
 }
}

void sensor2ISR() {
 if (!sensor2Triggered) { 
   timeSensor2 = micros(); 
   sensor2Triggered = true;
 }
}
