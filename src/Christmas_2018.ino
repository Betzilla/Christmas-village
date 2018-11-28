#include <Servo.h>

#define echoPin 11 // Echo Pin
#define trigPin 12 // Trigger Pin
#define LEDPin 4 // Onboard LED
#define TREEPin 2 // Onboard LED

#define SERIAL_BAUDRATE 9600
#define SERVO_PIN 9

//int maximumRange =  100; // Maximum range needed
//int minimumRange = 0; // Minimum range needed

//int switchState = 0;
Servo myServo;

void initDetection() {
  ///////////////////proximity sensor
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 

  digitalWrite(trigPin, LOW);
}

void turnAllLedsOff() {
  digitalWrite(LEDPin, LOW); 
  digitalWrite(TREEPin, LOW); 
}

void turnHouseLedOn() {
  //House LED turns on
  digitalWrite(LEDPin, HIGH); 
}

void turnTreeLedOn() {
  digitalWrite(TREEPin, HIGH); 
}

void turnTreeLedOff() {
  digitalWrite(TREEPin, LOW);
}

int DivisibleBy8(int n) 
{ 
  return (((n >> 3) << 3) == n); 
} 
  
int DivisibleBy16(int n) 
{ 
  return (((n >> 4) << 4) == n); 
} 

void toggleTreeLedBasedOnAngle(angle) {
  // Toggle LED every 8 degrees
  if (DivisibleBy16(angle)) {
    turnTreeLedOff();
  } else if (DivisibleBy8(angle)) {
    turnTreeLedOn();
  }
}

void servoTurn180DegreesCounterClockwise() {
  int pos; //variable to store the servo position
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myServo.write(pos);              // tell servo to go to position in variable 'pos'
      toggleTreeLedBasedOnAngle(pos);
      delay(15);                       // waits 15ms for the servo to reach the position
  }
} 

void servoTurn180DegreesClockwise() {
  int pos;
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    toggleTreeLedBasedOnAngle(pos);
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

void setup() {
 Serial.begin (SERIAL_BAUDRATE);

   //Motor
 myServo.attach(SERVO_PIN);
 
 //proximity sensor
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 //LEDs
 pinMode(LEDPin, OUTPUT);
 pinMode(TREEPin, OUTPUT);
}

void loop() {
  initDetection();

  long duration, distance; // Duration used to calculate distance
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58;
  //Serial.println(distance);


  /////////////////////INTERACTIONS BEGIN 
  if (distance < 100) {
    //House LED turns on
    turnHouseLedOn();

    //Motor
    servoTurn180DegreesCounterClockwise();
    servoTurn180DegreesClockwise();
  } else {
    turnAllLedsOff();
  }
}
