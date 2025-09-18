#include <Servo.h>

//for IR sensors
#define entrySensorPin 2
#define exitSensorPin 3

// servo
Servo entryGate;
Servo exitGate;

// Gate positions
int gateOpen = 90;  // Open position
int gateClosed = 0; // Closed position

void setup() {
  //servos to PWM pins
  entryGate.attach(5); // entery
  exitGate.attach(6);  // exit

  //IR sensor pins
  pinMode(entrySensorPin, INPUT);
  pinMode(exitSensorPin, INPUT);

  // Start with gates closed
  entryGate.write(gateClosed);
  exitGate.write(gateClosed);
}

void loop() 
{
  int entrySensorState = digitalRead(entrySensorPin);
  int exitSensorState = digitalRead(exitSensorPin);

  // Check entry
  if (entrySensorState == LOW) 
  { 
    entryGate.write(gateOpen);   
    delay(3000);                 
    entryGate.write(gateClosed); 
  }

  // Check exit
  if (exitSensorState == LOW) {
    exitGate.write(gateOpen);    
    delay(3000);                 
    exitGate.write(gateClosed);  
  }
}
