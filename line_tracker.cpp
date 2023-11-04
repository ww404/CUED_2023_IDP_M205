/* Notes to Bram: pins select using only numbers are digital pins, pins selected using A followed by a number are analogue pins
Void before a function basically tell the program to not run the function at that point, allowing you to define a function for use later
bool left defines left as a boolian function that can only be true or false.

*/

// From the motor sample code, pre-setup
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *Motor_L = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor Motor_R = AFMS.getMotor(2);




// Function: track white lines and turn or keep following the line when there is a intersection


int leftlinesensorPin = 2; // Connect left line sensor to input pin 2
int rightlinesensorPin = 3; // Connect right line sensor to input pin 3


// This is a function telling it to move forward until the line detector notices something different

// Moving forward??? --> I'm (Bram) going to assume you mean left
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


// Turning left??? --> I'm (Bram) going to assume you mean forward
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

// Commented out extra input readings as I (Bram) don't think they are needed, i.e each sensor only has one input pin.
// Also correct for the previous change made witht regard to sensor input by removing the _1 from both "active sensors"


int valLeft_1 = digitalRead(leftlinesensorPin); // read left input value
//int valLeft_2 = digitalRead(leftlinesensorPin_2); 
// Serial.print(valLeft_1);
int valRight_1 = digitalRead(rightlinesensorPin); // read right input value
//int valRight_2 = digitalRead(rightlinesensorPin_2); 


// Serial.println(valRight_1); delay(100); // prinln starts a new line after the output


/*
I'm (Bram) not entirely sure about this, it's probably coirrect but I've written an alternative below so wehave two things to test

stop = (! valRight_2 == valRight_1)
turn_left = (valRight_2 == HIGH)

if (valRight_2 == valRight_1) {
    //keep going straight
    MoveForward(stop)
}
else if (valRight_1 == HIGH) {
    //turn left 90 degrees and then go straight
    TurnLeft(turn_left)
}

*/


if (valLeft_1 == HIGH) {
    Motor_R->setSpeed(255)
    Motor_L->spetSpeed(127)
    Delay(10)

    //Again modify the delay as required to achieve a suitable amount of rotation
}

if (valLeft_2 == HIGH) {
    Motor_L->setSpeed(255)
    Motor_R->spetSpeed(127)
    Delay(10)

    // Same as above
}

else {
    MoveForward(stop)
}

}
