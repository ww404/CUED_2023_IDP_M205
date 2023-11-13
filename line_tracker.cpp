
// From the motor sample code, pre-setup
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor_L = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(2);




// Function: track white lines and turn or keep following the line when there is a intersection
int led = 2;
int leftlinesensorPin = 3; // Connect left line sensor to input pin 2
int rightlinesensorPin = 4; // Connect right line sensor to input pin 3
int centerlinesensorPin = 5;


// This is a function telling it to move forward until the line detector notices something different

void TurnLeft (bool left){
    while (left) {

        Motor_L->run(FORWARD);
        Motor_R->run(FORWARD);
        Motor_L->setSpeed(255);
        Motor_R->setSpeed(255);
    }
    // Delay needs to be determined, probably by trial and error to ensure a turn of ~90 degrees
    delay(10);
}

void MoveForward (bool stop){
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
pinMode(leftlinesensorPin, INPUT); // declares left linesensor as an input
pinMode(rightlinesensorPin, INPUT); // declares right linesensor as an input
pinMode(centerlinesensorPin, INPUT); 
pinMode(led, OUTPUT);



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
  Motor_L->setSpeed(255);
  Motor_R->setSpeed(255);
  Motor_L->run(FORWARD);
  Motor_R->run(BACKWARD);
  // turn on motor
  Motor_L->run(RELEASE);
  Motor_R->run(RELEASE);

}



void loop(){

// Also correct for the previous change made witht regard to sensor input by removing the _1 from both "active sensors"

digitalWrite(led, HIGH);
int valLeft_1 = digitalRead(leftlinesensorPin); // read left input value
int valRight_1 = digitalRead(rightlinesensorPin); // read right input value
int valCenter = digitalRead(centerlinesensorPin); 

while (valCenter == LOW){

if (valRight_1 == HIGH) {
    Motor_R->setSpeed(255);
    Motor_L->setSpeed(127*0.54);

    //Again modify the delay as required to achieve a suitable amount of rotation
}

else if (valLeft_1 == HIGH) {
    Motor_L->setSpeed(255*0.54);
    Motor_R->setSpeed(127);


    // Same as above
}

else {
        Motor_L->run(BACKWARD);
        Motor_R->run(FORWARD);
        Motor_L->setSpeed(255*0.54);
        Motor_R->setSpeed(255);
}

}

  Motor_L->run(FORWARD);
  Motor_R->run(FORWARD);
  Motor_L->setSpeed(255*0.54);
  Motor_R->setSpeed(255);
  delay(1850); 
}