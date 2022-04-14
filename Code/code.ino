#include <Servo.h>

const int TRIG_PIN = 6;
const int ECHO_PIN = 7;

const int ECHO_PIN2 = 10;
const int TRIG_PIN2 = 9;

//leds
const int red_led = 3;
const int green_led = 4;
const int yellow_led = 5;

bool is_user = true;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement

//states
enum { CLOSE, OPEN} currentState = CLOSE;

byte servoPos = 0;

Servo servo;

void setup() {
  // put your setup code here, to run once:

  servo.attach(8);

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN2, OUTPUT);
 
  //Set Echo pin as input to measure the duration of
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN2, INPUT);

  //led pins
  pinMode(red_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Clears the trigPin condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Clears the trigPin condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
//  Serial.print("Distance: ");
//  Serial.print(distance);
//  Serial.println(" cm");
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(ECHO_PIN2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  // Displays the distance on the Serial Monitor
//  Serial.print("Distance2: ");
//  Serial.print(distance2);
//  Serial.println(" cm");

  switch (currentState)
  {
    case CLOSE:
      servoPos = 0;
      servo.write(servoPos);
      if (distance < 50)
      {
        currentState = OPEN;
      }
      break;

    case OPEN:
      servoPos = 110;
      servo.write(servoPos);
      if (distance > 50)
      {
        currentState = CLOSE;
      }
      break;
  }//switch


  //if(distance2 < 50){
    //servo.write(110);
    //delay(3000); //
  //}
  //else{
    //servo.write(0);
    //delay(30);
  //}
   

}
