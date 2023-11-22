#include <Adafruit_MotorShield.h>
#define MAX_RANG 520  //the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define  ADC_SOLUTION 1023.0


// Pin assignments
const int leftLineSensorPin = 2; 
const int rightLineSensorPin = 3; 
const int centerLineSensorPin_Left = 4;
const int centerLineSensorPin_Right = 5;
const int magInputPin = 6;
const int sensityPin = A3;
const int greenLEDpin = 7;
const int redLEDpin = 8;
const int blueLEDpin = 9;


// Motor setup
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *Motor_L = AFMS.getMotor(2);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(1);


// Global variables
const long blinkInterval = 250; // The blue led blinking interval
int blueLedState = LOW;
unsigned long previousMillis = 0;
unsigned long currentMillis = millis();

bool pickedUp = false;    // if the block is picked up
//int Total_Junction = 0;
bool reachedJunction0 = false;
const int speed = 180;    //risky = may want to calibrate to speed 
const int cornerSpeed = 120;
int junctionCounter = 0;


//Define functions
//do 4 functions (all difre) 
//line-tracking code 


void correctRight() { 
//if (valCenter_left == HIGH && valCenter_right == LOW) this goes in main loop 
  Motor_L -> run(FORWARD);
  Motor_R -> run(FORWARD);  
  Motor_L -> setSpeed(speed*0.8);
  Motor_R -> setSpeed(speed);
  if (currentMillis - previousMillis >= blinkInterval) {

    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    blueLedState = !blueLedState;

    // set the LED with the ledState of the variable:
    digitalWrite(blueLEDpin, blueLedState);
    return;
  }

  // Again modify the delay as required to achieve a suitable amount of rotation
} 


void correctLeft() { //for line following
  // else if (valCenter_left == LOW && valCenter_right == HIGH) {
  Motor_L -> run(FORWARD);
  Motor_R -> run(FORWARD);  
  Motor_R -> setSpeed(speed*0.8); // may have to lower this
  Motor_L -> setSpeed(speed);
  if (currentMillis - previousMillis >= blinkInterval) {

    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    blueLedState = !blueLedState;

    // set the LED with the blueLedState of the variable:
    digitalWrite(blueLEDpin, blueLedState);
    return;
  }
}


void moveForward() {
  Motor_L -> run(FORWARD);
  Motor_R -> run(FORWARD);  
  Motor_R -> setSpeed(speed);
  Motor_L -> setSpeed(speed);
  if (currentMillis - previousMillis >= blinkInterval) {

    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    blueLedState = !blueLedState;

    // set the LED with the blueLedState of the variable:
    digitalWrite(blueLEDpin, blueLedState);
    return;
  }
}


void TurnLeft () {

  // int valCenter_left = digitalRead(centerLineSensorPin_Left); 
  // int valCenter_right = digitalRead(centerLineSensorPin_Right); 
  // int valLeft = digitalRead(leftLineSensorPin);
 
  Motor_L -> run(BACKWARD);
  Motor_R -> run(FORWARD);
  Motor_L -> setSpeed(cornerSpeed); 
  Motor_R -> setSpeed(cornerSpeed);
  delay(700);

  while ((digitalRead(centerLineSensorPin_Left) == LOW && 
          digitalRead(centerLineSensorPin_Right) == LOW) || 
          digitalRead(leftLineSensorPin) == LOW) {
    Motor_L -> run(BACKWARD);
    Motor_R -> run(FORWARD);
    Motor_L -> setSpeed(cornerSpeed); 
    Motor_R -> setSpeed(cornerSpeed);
    delay(20);
  }
}


void TurnRight () {

  // int valCenter_left = digitalRead(centerLineSensorPin_Left); 
  // int valCenter_right = digitalRead(centerLineSensorPin_Right); 
  // int valLeft = digitalRead(leftLineSensorPin);

  Motor_L -> run(FORWARD);
  Motor_R -> run(BACKWARD);
  Motor_L -> setSpeed(cornerSpeed); 
  Motor_R -> setSpeed(cornerSpeed);
  delay(700);


  while ((digitalRead(centerLineSensorPin_Left) == LOW && 
          digitalRead(centerLineSensorPin_Right) == LOW) || 
          digitalRead(rightLineSensorPin) == LOW) {
    Motor_L -> run(FORWARD);
    Motor_R -> run(BACKWARD);
    Motor_L -> setSpeed(cornerSpeed); 
    Motor_R -> setSpeed(cornerSpeed);
    delay(20);
  }
}


void Stop () {
  Motor_L -> run(FORWARD);
  Motor_R -> run(FORWARD);
  Motor_L -> setSpeed(0); 
  Motor_R -> setSpeed(0);
}


void Reverse (int speed) {
  Motor_L -> run(BACKWARD);
  Motor_R -> run(BACKWARD);
  Motor_L -> setSpeed(speed);
  Motor_R -> setSpeed(speed);
}



void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Program started");

  // Configuring pins
  pinMode(leftLineSensorPin, INPUT);
  pinMode(rightLineSensorPin, INPUT);
  pinMode(centerLineSensorPin_Left, INPUT);
  pinMode(centerLineSensorPin_Right, INPUT);

  pinMode (magInputPin, INPUT);
  pinMode (sensityPin, INPUT) ;
  pinMode (greenLEDpin, OUTPUT);
  pinMode (redLEDpin, OUTPUT);
  pinMode (blueLEDpin, OUTPUT);

  // Set up motors
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
      // Set the speed to start, from 0 (off) to 255 (max speed)
    Motor_R -> setSpeed(255);
    Motor_L -> setSpeed(255);
    Motor_R -> run(FORWARD);
    Motor_L -> run(FORWARD);

    //turn on motor
    Motor_R -> run(RELEASE);
    Motor_L -> run(RELEASE);
  }
}



void loop() {

  //Read sensors, put it here so you don't have to repeatedly code this
  int valCenter_left = digitalRead(centerLineSensorPin_Left); 
  int valCenter_right = digitalRead(centerLineSensorPin_Right); 
  int valLeft = digitalRead(leftLineSensorPin); // read left input value
  int valRight = digitalRead(rightLineSensorPin); // read right input value
  float sensity_t = analogRead(sensityPin);
  bool magnetic = digitalRead(magInputPin);
  int block_distance = sensity_t * MAX_RANG / ADC_SOLUTION; 


  //Block Detection
  if ((block_distance <= 5) && (!pickedUp)) {
    pickedUp = true;
    if (magnetic == HIGH) { // check if the input is HIGH
      digitalWrite(redLEDpin, HIGH);
      delay(6000);
      digitalWrite(redLEDpin, LOW); // turn red LED on
    } else {
      digitalWrite(greenLEDpin, HIGH);
      delay(6000); 
      digitalWrite(greenLEDpin, LOW); // turn green LED on
    }  
  }

  //second attempt at junctions
  if (valLeft == 1 || valRight == 1) {
    switch (junctionCounter) {
      
      case 0:
        moveForward();
        junctionCounter++;
        delay(200);
        break;

      case 1:
        TurnRight();
        junctionCounter++;
        moveForward();
        delay(200);
        break;

      case 2:
        moveForward();
        junctionCounter++;
        delay(200);
        break;

      case 3:
        TurnRight();
        junctionCounter++;
        moveForward();
        delay(200);
        break;

      case 4:
        TurnRight();
        junctionCounter++;
        moveForward();
        delay(200);
        break;

      case 5:
        moveForward();
        junctionCounter++;
        delay(200);
        break;
    }
  }
   

  //line following
  else if (valCenter_left == 1 && valCenter_right == 0) {
    correctRight();
  } else if (valCenter_left == 0 && valCenter_right == 1) {
    correctLeft();
  } else{
    moveForward();
  }
}
   

