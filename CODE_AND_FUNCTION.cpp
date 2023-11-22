//#include "C:\Users\BramH\Documents\Arduino\Functions_Corrected\Functions_Corrected.ino"
//#include "/Users/v.w./Desktop/cambridge/IB/LAB/IDP/CUED_2023_IDP_M205/CORRECTED_FUNCTION"
//#include "CORRECTED_FUNCTION.cpp"
#include <Adafruit_MotorShield.h>
#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define  ADC_SOLUTION
// logic for junctions and normally turning
// functions we are using:
//      moveForward     moves forward until deteects a block, and calls function Block
//      Block           when a block has been found, detect and shine LED and clamp it together (all that jazzzzzz)
//      TurnLeft and TurnRight      turns 90 degrees or until some sensor changes 
// sensors we are using
//      LineSensor_Left, LineSensor_Right, LineSensor_Center
//      MagneticSensor
//      UltraSonicSensor
// motors we are using
//      MotorLeft and MotorRight
//      Servor (for clampling block)
// LEDs we are using
//      Red and Green for testing magnetic
//      Blue for indicating moving
//      White for illuminating the line-sensors


extern int leftLineSensorPin; 
extern int rightLineSensorPin; 
extern int centerLineSensorPin_Left;
extern int centerLineSensorPin_Right;
extern int magInputPin;
extern int sensityPin ;
extern int greenLEDpin;
extern int redLEDpin;
extern int blueLEDpin;

int valLeft = digitalRead(leftLineSensorPin); // read left input value
int valRight = digitalRead(rightLineSensorPin); // read right input value
int valCenter_left = digitalRead(centerLineSensorPin_Left); 
int valCenter_right = digitalRead(centerLineSensorPin_Right);
float sensity_t = analogRead(sensityPin);
float dist_t;

int leftLineSensorPin = 2; 
int rightLineSensorPin = 3; 
int centerLineSensorPin_Left = 4;
int centerLineSensorPin_Right = 5;
int magInputPin = 6;
int sensityPin = A3;
int greenLEDpin = 7;
int redLEDpin = 8;
int blueLEDpin = 9;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor_L = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(2);

int Magnetic = digitalRead(magInputPin);
int stop_LED = 0;

int speed = 180;
extern Adafruit_MotorShield AFMS;
extern Adafruit_DCMotor *Motor_L;
extern Adafruit_DCMotor *Motor_R;

void LineTracking(int valLeft, int valRight, int valCenter_left, int valCenter_right, int speed){

// after testing the four_sensors_line_tracking code, can change all this into that tracking code.

if (valLeft == LOW && valRight == LOW){

  if (valCenter_left == LOW && valCenter_right == HIGH) {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_L->setSpeed(speed*0.5);
    Motor_R->setSpeed(speed);

    //Again modify the delay as required to achieve a suitable amount of rotation
  } 

  else if (valCenter_right == LOW && valCenter_left == HIGH) {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(speed*0.5);
    Motor_L->setSpeed(speed);


    // Same as above
  }

  else {
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(speed);
    Motor_L->setSpeed(speed);
  }
}

}
    

void moveForward(int valLeft, int valRight, int valCenter_left, int valCenter_right, int speed){
  //dist_t = sensity_t * MAX_RANG / ADC_SOLUTION;
  LineTracking(valLeft, valRight, valCenter_left, valCenter_right, speed);


  //if (dist_t < 5) {
  //  Block();
  //} 

  //else {
  //  LineTracking();
  //}
}
// if angles = 90, then it turns exactly 90 degrees to the left or right
// else, it is correcting not following lines and turns until it is Straight again

void TurnLeft (int angles, int speed){
    Motor_L->run(FORWARD);
    Motor_R->run(BACKWARD);
    Motor_L->setSpeed(speed); 
    Motor_R->setSpeed(speed);
    delay(angles * 557/90);
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(speed);
    Motor_L->setSpeed(speed);
    delay(100);  

}

void TurnRight (int angles, int speed){
    Motor_L->run(BACKWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(speed); 
    Motor_R->setSpeed(speed);
    delay(angles * 557/90);
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);  
    Motor_R->setSpeed(speed);
    Motor_L->setSpeed(speed);
    delay(100);  
}


void Stop (){
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(0); 
    Motor_R->setSpeed(0);
}

void Reverse (int speed){
    Motor_L->run(BACKWARD);
    Motor_R->run(BACKWARD);
    Motor_L->setSpeed(speed);
    Motor_R->setSpeed(speed);


}
/*
void Block (void){

  // Detects if the block is magnetic or not
  // Flashes the LED light
  // Clamps the clamp 

  Magnetic = digitalRead(magInputPin);

  float block_distance;

  // read the value from the sensor:
  sensity_t = analogRead(sensityPin);
  block_distance = sensity_t * MAX_RANG / ADC_SOLUTION;
  if (block_distance <= 5){
    Jaws(true);

    if (block_distance <= 1) {

     // Gemma's code

        
      if (stop_LED = 0) {
        int magnetic = 0; // variable for reading the pin status
      
        if (magnetic == HIGH) { // check if the input is HIGH
          digitalWrite(redLEDpin, HIGH);
          delay(6000);
          digitalWrite(redLEDpin, LOW); // turn red LED on
        }  
                
        else {
          digitalWrite(greenLEDpin, HIGH);
          delay(6000); 
          digitalWrite(greenLEDpin, LOW);// turn green LED on
       }

       stop_LED = 1;
      } 
    }
         
  }   

}



void Jaws(bool){
    #include <Servo.h>
    Servo myservo; // create servo object to control a servo

    int pos = 0; // variable to store the servo position
    myservo.attach(9); // attaches the servo on pin 9 to the servo object

    int closed_angle;
    if (true){
        closed_angle = 180;
    }else {
        closed_angle = 0;
    }
    
    myservo.write(closed_angle); 
}
*/
 

void Moving_Light() {

// Megan's code - flashing blue light, use function when robot is moving.

    digitalWrite(blueLEDpin, HIGH);
    delay(250);
    digitalWrite(blueLEDpin, LOW);
    delay(250);

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

  int Pass_Zero = 0;
  int Blocks = 0;
  int Turn_Left_count = 0;
  int Turn_Right_count = 0;
  int Ignore_Turn = 0;
  int Total_Junction = 0;
  extern int angles;

}



void loop(){
  int valLeft = digitalRead(leftLineSensorPin); // read left input value
  int valRight = digitalRead(rightLineSensorPin); // read right input value
  int valCenter_left = digitalRead(centerLineSensorPin_Left); 
  int valCenter_right = digitalRead(centerLineSensorPin_Right); 
    speed = 180;

  int Pass_Zero, Blocks, Turn_Left_count, Turn_Right_count, Ignore_Turn, Total_Junction, Total_junction;
  // Actions:
  //      boolean values:
  bool Found_Block, Magnetic;
  bool Straight = (valLeft ==0 && valRight == 0);
  bool Junction_Left = (valLeft == 1 && valRight == 0 && valCenter_left == 1 && valCenter_right == 1);
  bool Junction_Right =  (valLeft == 0 && valRight == 1 && valCenter_left == 1 && valCenter_right == 1);
  bool Junction_Zero = (valLeft == 1 && valRight == 1 && valCenter_left == 1 && valCenter_right == 1);
  bool Junction_Five = (valLeft == 1 && valRight == 1 && valCenter_left == 0 && valCenter_right == 0);

// Junctions:
// Junction 5 = Turn_Right_count ==0 && Turn_Left_count ==0 && Ignore_Turn == 0 && Junction_Five == true;
// Junction 4 = Turn_Right_count ==1 && Turn_Left_count ==0 && Ignore_Turn == 0 && Junction_Right == true;
// Junction 3: Turn_Right_count ==1, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true
// Junction 2: Turn_Right_count ==2, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true
// Junction 1: Turn_Right_count ==3, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true


Total_junction = Turn_Left_count + Turn_Right_count + Ignore_Turn + Pass_Zero;

// What is going to happen IDEALLY:

//if(Blocks == 0){

    if (Junction_Zero == true and Total_Junction == 0) {
        Pass_Zero = Pass_Zero + 1;
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }
          
    else if (Junction_Five == true and Total_Junction == 1){ // at Junction 5
      TurnRight(90, speed);
      Turn_Right_count = Turn_Right_count + 1;
      moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
      //if (Found_Block){
        //TurnLeft(180);
        //moveForward();
        //delay(2000);
      //break;
      //}
    }

    else if (Junction_Right == true and Total_Junction == 2){ // at Junction 4
        Ignore_Turn = Ignore_Turn + 1;
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Right == true and Total_Junction == 3){ // at Junction 3
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(90, speed);
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Right == true and Total_Junction == 4){ // at Junction 2
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(90, speed);
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Right == true and Total_Junction == 5){ // at Junction 1
        Ignore_Turn = Ignore_Turn + 1;
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Zero == true and Total_Junction == 6 ) { // at Junction 0 return
        Pass_Zero = Pass_Zero + 1;
        TurnLeft(90, speed);
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Zero == true and Total_Junction == 6 ) { // at the starting point
        if(Magnetic){
            TurnRight(90, speed);
        }
        else{
            TurnLeft(90, speed);
        }
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Five == true and Total_Junction == 7 ) { // at one of those colorful boxes
        Total_Junction = Total_Junction + 1;
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
        delay(100);
        Stop();
        Reverse(speed);
        delay(2000);
        TurnLeft(180, speed);
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }

    else if (Junction_Five == true and Total_Junction == 8 ) { // back in origin
        if(Magnetic){
            TurnLeft(90, speed);
        }
        else{
            TurnRight(90, speed);
        }
        Blocks = 1;
    }

    else {
        moveForward(valLeft, valRight, valCenter_left, valCenter_right, speed);
    }
    
    LineTracking(valLeft, valRight, valCenter_left, valCenter_right, speed);
  }
//}

