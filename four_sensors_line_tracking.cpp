#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor_L = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(2);


int leftLineSensorPin = 2;
int rightLineSensorPin = 3; 
int centerLineSensorPin_Left = 4;
int centerLineSensorPin_Right = 5;


void TurnLeft (void){
    Motor_L->run(BACKWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(255);
    Motor_R->setSpeed(255);
    delay(1000); 
    }

void TurnRight (void){
    Motor_L->run(FORWARD);
    Motor_R->run(BACKWARD);
    Motor_L->setSpeed(255);
    Motor_R->setSpeed(255);
    delay(1000); 
    }

void moveForward (bool stop){
    while (!stop) {
        // motor speeds not corrected for the different running speeds on the motors on the current prototype (#1)

        Motor_L->run(FORWARD);
        Motor_R->run(BACKWARD);
        Motor_L->setSpeed(255);
        Motor_R->setSpeed(255);
    }
}



void setup() {

// setup for line_sensors
Serial.begin(9600); // Init the serial port
pinMode(leftLineSensorPin, INPUT); // declares left linesensor as an input
pinMode(rightLineSensorPin, INPUT); // declares right linesensor as an input
pinMode(centerLineSensorPin_Left, INPUT);
pinMode(centerLineSensorPin_Right, INPUT);

// copying the setup for motors
Serial.begin(9600);           // set up Serial library at 9600 bps
Serial.println("Adafruit Motorshield v2 - Motors and line detector test");


if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
}
  Serial.println("Motor Shield found.");



  // Set the speed to start, from 0 (off) to 255 (max speed), set to 255 to start the robot moving
  Motor_L->run(FORWARD);
  Motor_R->run(BACKWARD);  
  Motor_L->setSpeed(0);
  Motor_R->setSpeed(0);

  // turn on motor
  Motor_L->run(RELEASE);
  Motor_R->run(RELEASE);

}



void loop(){

int valLeft = digitalRead(leftLineSensorPin); // read left input value
int valRight = digitalRead(rightLineSensorPin); // read right input value
int valCenter_left = digitalRead(centerLineSensorPin_Left); 
int valCenter_right = digitalRead(centerLineSensorPin_Right); 
if (valLeft == LOW && valRight == LOW){


  if (valCenter_left == LOW && valCenter_right == HIGH) {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_L->setSpeed(255*0.5);
    Motor_R->setSpeed(255);

    //Again modify the delay as required to achieve a suitable amount of rotation
  } 

  else if (valCenter_right == LOW && valCenter_left == HIGH) {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(255*0.5);
    Motor_L->setSpeed(255);


    // Same as above
  }

  else {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(255);
    Motor_L->setSpeed(255);
  }
}



if (valLeft == HIGH) {
    if (valRight == HIGH){
        TurnRight();
    }else {
        TurnLeft();
    }
    }
else if (valLeft == LOW and valRight == HIGH) {
    TurnRight();
}

}
