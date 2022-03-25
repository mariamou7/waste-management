// Pins
const int TRIG_PIN = 6;
const int ECHO_PIN = 7;
const int ECHO_PIN2 = 10;
const int TRIG_PIN2 = 9;

// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;

void setup() {

  // The Trigger pin will tell the sensor to range find
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode(TRIG_PIN2, OUTPUT);
  digitalWrite(TRIG_PIN2, LOW);

  //Set Echo pin as input to measure the duration of 
  //pulses coming back from the distance sensor
  pinMode(ECHO_PIN, INPUT);
  pinMode(ECHO_PIN2, INPUT);

  // We'll use the serial monitor to view the sensor output
  Serial.begin(9600);
}

void loop() { //=================================================void loop=============================================
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float cm2;
  //float inches;

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
    int cm_a = pulse_width_a / 58.0;
    //inches = pulse_width / 148.0;
  
    // Print out results
    if ( pulse_width_a > MAX_DIST ) {
      Serial.println("Out of range");
    } 
    else {
      Serial.print(cm_a);
      Serial.print(" cm \t");
      //Serial.print(inches);
      //Serial.println(" in");
    }
  }
  
  if (digitalRead(ECHO_PIN2) == 0) { //---------------------------------------------reads the second sensor-----------------------
    Serial.println("--------------sensor_b--------------");
    
    // Measure how long the echo pin was held high (pulse width)
    // Note: the micros() counter will overflow after ~70 min
    int tb1 = micros();
    while ( digitalRead(ECHO_PIN2) == 1);
    int tb2 = micros();
    int pulse_width_b = tb2 - tb1;
  
    // Calculate distance in centimeters and inches. The constants
    // are found in the datasheet, and calculated from the assumed speed
    //of sound in air at sea level (~340 m/s).
    int cm_b = pulse_width_b / 58.0;
    //inches = pulse_width / 148.0;
  
    // Print out results
    if ( pulse_width_b > MAX_DIST ) {
      Serial.println("Out of range");
    } else {
      Serial.print(cm_b);
      Serial.print(" cm \t");
      //Serial.print(inches);
      //Serial.println(" in");
    }
  }

  // Wait at least 60ms before next measurement
  delay(5000);
}
