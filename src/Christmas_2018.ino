#include <Servo.h>
Servo myServo;
int pos =0; //variable to store the servo position

#define echoPin 11 // Echo Pin
#define trigPin 12 // Trigger Pin
#define LEDPin 4 // Onboard LED
#define TREEPin 2 // Onboard LED

//int maximumRange =  100; // Maximum range needed
//int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
//int switchState = 0;


void setup() {
 Serial.begin (9600);

   //Motor
 myServo.attach(9);
 
 //proximity sensor
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);

 //LEDs
 pinMode(LEDPin, OUTPUT);
 pinMode(TREEPin, OUTPUT);
}

void loop() {
  
///////////////////proximity sensor
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58;
//Serial.println(distance);

/////////////////////INTERACTIONS BEGIN 
if (distance < 100){
//Motor
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
//House LED turns on
digitalWrite(LEDPin, HIGH); 

  //LED on tree flashes
digitalWrite(TREEPin, HIGH); 
delay(100);
digitalWrite(TREEPin, LOW);
delay(100);

digitalWrite(TREEPin, HIGH); 
delay(100);
digitalWrite(TREEPin, LOW);
delay(100);

digitalWrite(TREEPin, HIGH); 
delay(100);
digitalWrite(TREEPin, LOW);
delay(100);
 }
 
 else {
digitalWrite(LEDPin, LOW); 
digitalWrite(TREEPin, LOW); 
}


}
