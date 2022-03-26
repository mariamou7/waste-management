// Pins

//sensors
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int ECHO_PIN2 = 10;
const int TRIG_PIN2 = 9;

//leds
const int red_led = 3;
const int green_led = 4;
const int yellow_led = 5;

//servo
#include <Servo.h>

const int val = 90;

Servo servo;


bool is_user = true;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {
  //servo
  servo.attach(9);
  
  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(TRIG_PIN2, OUTPUT);
  digitalWrite(TRIG_PIN2, LOW);
  
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

void loop() { //=================================================void loop=============================================
//  unsigned long t1;
//  unsigned long t2;
    unsigned long pulse_width_a;
    unsigned long pulse_width_b;
    float cm_a;
    float cm_b;

  // Hold the trigger pin high for at least 10 us
  digitalWrite(TRIG_PIN, HIGH);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(TRIG_PIN2, LOW);

  // Wait for pulse on echo pin
  if (digitalRead(ECHO_PIN) == 0) {  //-----------------------------------------reads the first sensor----------------------
    Serial.println("--------------sensor_a--------------");
    
    int ta1 = micros();
    while ( digitalRead(ECHO_PIN) == 1);
    int ta2 = micros();
    int pulse_width_a = ta2 - ta1;
  
    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed
    //of sound in air at sea level (~340 m/s).
    cm_a = pulse_width_a / 58.0;
    //inches = pulse_width / 148.0;
  
    // Print out results
    if ( pulse_width_a > MAX_DIST ) {
      Serial.println("Out of range");
    } 
    else {
      Serial.print(cm_a);
      Serial.print(" cm \t");
//      if (cm_a <= 50) {
//        digitalWrite(green_led, HIGH);
//        
//      }
//      else {
//        digitalWrite(green_led, LOW);
//      }
      
    }
  }
  
  if (digitalRead(ECHO_PIN2) == 0) { //---------------------------------------------reads the second sensor-----------------------
    Serial.println("--------------sensor_b--------------");
    
    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    int tb1 = micros();
    while ( digitalRead(ECHO_PIN2) == 1);
    int tb2 = micros();
    pulse_width_b = tb2 - tb1;
  
    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed
    //of sound in air at sea level (~340 m/s).
    cm_b = pulse_width_b / 58.0;
    //inches = pulse_width / 148.0;
  
    // Print out results
    if ( pulse_width_b > MAX_DIST ) {
      Serial.println("Out of range");
    } 
    else {
      Serial.print(cm_b);
      Serial.print(" cm \t");
      
      if ( cm_b <= 100 ) { //an kapoios plhsiasei ston kado
        Serial.println("user found");
        if (is_user == true) { //TODO: na ftiaxoume thn efarmogh
          servo.write(val); // anoigei to kapaki
          digitalWrite(red_led, HIGH); // TODO: an kapoios plhsiasei ton kado wvris na thelei na petajei kati
          Serial.println("opening...");
          delay(3000);
          digitalWrite(red_led, LOW);
          digitalWrite(green_led, HIGH);
          Serial.println("you can throw rubish.");
          if (cm_a <= 10) { //otan petajei kapoios skoupidia mesa ston kadv
            delay(3000); // perimene 3 s
            Serial.println("closing...");
            servo.write(val - 90); // kleise to kapaki
            digitalWrite(green_led, LOW); //TODO: otan kapoios thelei na petajei panv apo 2 sakoules
           
            
          }
        }
      }
//      else {
//        servo.write(val - 90);
//        digitalWrite(red_led, LOW);
//      }
      
      
    }
  }

  // Wait at least 60ms before next measurement
  //delay(5);
}
