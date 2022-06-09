/*
  Smart ecogarbage bins final code
*/

#include <Servo.h>
#include <WiFi.h>

//Initializations
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;

const int TRIG_PIN_OUT = 9;
const int ECHO_PIN_OUT = 10;

int VOLT_PIN = A1; //initialize analog pin 2 as "voltPin"

bool is_user = true;

long duration; //variable for the duration of sound wave travel
int distance; //variable for the distance measurement

long durationOut; //variable for the duration of sound wave travel
int distanceOut; //variable for the distance measurement

//states
enum {CLOSE, OPEN} switchState = CLOSE;

byte servoPos = 0;

int bagCounter = 0;
int currentState = 0;
int previousState = 0;

Servo servo;

void setup() {
  //setup code here, runs once:

  servo.attach(12);

  //The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(TRIG_PIN_OUT, OUTPUT);
  
  //Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN_OUT, INPUT);

  pinMode(VOLT_PIN, INPUT); //initialize "VOLT_PIN" as an input

  //Wi-Fi connenction
  WiFi.begin("Android-Maria", "123456"); //Network name, network password
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  //We'll use the serial monitor to view the sensor output
  Serial.begin(9600);

}

void loop() {
  //main code here, runs repeatedly:

  //Clears the trigPin condition
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  //Clears the trigPin condition
  digitalWrite(TRIG_PIN_OUT, LOW);
  delayMicroseconds(2);

  //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  //Calculating the distance
  distance = duration * 0.034 / 2; //Speed of sound wave divided by 2 (go and back)

  //Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(10);

  //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIG_PIN_OUT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_OUT, LOW);

  //Reads the echoPin, returns the sound wave travel time in microseconds
  durationOut = pulseIn(ECHO_PIN_OUT, HIGH);
  //Calculating the distance of users
  distanceOut = durationOut * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  //Displays the distance of the out ultrasonic on the Serial Monitor
  Serial.print("Distance out: ");
  Serial.print(distanceOut);
  Serial.println(" cm");

  //delay(1000);

  switch (switchState)
    {
      case CLOSE:
        servoPos = 0;
        servo.write(servoPos);
        if (distanceOut < 50 && is_user == true)
        {
          switchState = OPEN;
        }
        break;

      case OPEN:
        servoPos = 120;
        servo.write(servoPos);

        if (distance <= 13){ 
          currentState = 1;
        }
        else {
          currentState = 0;
        }
 
        delay(500);
 
        if(currentState != previousState){
          if(currentState == 1){
            bagCounter = bagCounter + 1;
            Serial.print("Number of trash bags: ");
            Serial.println(bagCounter);
          }
          delay(2000);
        }

        if (distanceOut > 50)
        {
          switchState = CLOSE;
        }
        break;
    }

  //Calculating the battery charging voltage
  int volts = analogRead(VOLT_PIN);
  
  //Print the volts
  Serial.print("Volts: ");
  Serial.println(volts);
  
  float v12 = (volts*12.0)/1023; //convert the value of the analog measurement (0-1023) to volts (0-12)
  
  //Print the volts
  Serial.print("V12: ");
  Serial.println(v12);
  Serial.println("_________________");
}
