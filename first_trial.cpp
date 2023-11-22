#include "functions.h"
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

int leftLineSensorPin = 2;
int rightLineSensorPin = 3;
int centerLineSensorPin_Left = 4;
int centerLineSensorPin_Right = 5;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  Motor_R->setSpeed(255);
  Motor_L->setSpeed(255);
  Motor_R->run(FORWARD);
  Motor_L->run(FORWARD);
  // turn on motor
  Motor_R->run(RELEASE);
  Motor_L->run(RELEASE);

  pinMode(leftLineSensorPin, INPUT);
  pinMode(rightLineSensorPin, INPUT);
  pinMode(centerLineSensorPin_Left, INPUT);
  pinMode(centerLineSensorPin_Right, INPUT);
}



void loop(){
int valLeft = digitalRead(leftLineSensorPin); // read left input value
int valRight = digitalRead(rightLineSensorPin); // read right input value
int valCenter_left = digitalRead(centerLineSensorPin_Left); 
int valCenter_right = digitalRead(centerLineSensorPin_Right); 

// Actions:
//      boolean values:
bool Found_Block, Magnetic;
bool Straight = valLeft ==0 && valRight == 0;
bool Junction_Left = valLeft == 1 && valRight == 0 && valCenter_left == 1 && valCenter_left == 1;
bool Junction_Right =  valLeft == 0 && valRight == 1 && valCenter_left == 1 && valCenter_left == 1;
bool Junction_Zero = valLeft == 1 && valRight == 1 && valCenter_left == 1 && valCenter_left == 1;
bool Junction_Five = valLeft == 1 && valRight == 0 && valCenter_left == 0 && valCenter_left == 1;

// Junctions:
// Junction 5 = Turn_Right_count ==0 && Turn_Left_count ==0 && Ignore_Turn == 0 && Junction_Five == true;
// Junction 4 = Turn_Right_count ==1 && Turn_Left_count ==0 && Ignore_Turn == 0 && Junction_Right == true;
// Junction 3: Turn_Right_count ==1, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true
// Junction 2: Turn_Right_count ==2, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true
// Junction 1: Turn_Right_count ==3, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == true

// counts
Pass_Zero = 0;
Blocks = 0;
Turn_Left_count = 0;
Turn_Right_count = 0;
Ignore_Turn = 0;
Total_Junction = Turn_Left_count + Turn_Right_count + Ignore_Turn + Pass_Zero;

// What is going to happen IDEALLY:

if(Blocks == 0){

    if (Junction_Zero == True and Total_Junction == 0) {
        Pass_Zero = Pass_Zero + 1;
        moveForward();
    }
          
    if (Junction_Five == True and Total_Junction == 1){ // at Junction 5
        TurnRight(angles = 90);
        Turn_Right_count = Turn_Right_count + 1;
        moveForward();
        if (Found_Block){
            TurnLeft(180);
            moveForward();
            delay(2000);
            break;
        }
    }

    if (Junction_Right == True and Total_Junction == 2){ // at Junction 4
        Ignore_Turn = Ignore_Turn + 1;
        moveForward();
    }

    if (Junction_Right == True and Total_Junction == 3){ // at Junction 3
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(angles = 90);
        moveForward();
    }

    if (Junction_Right == True and Total_Junction == 4){ // at Junction 2
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(angles = 90);
        moveForward();
    }

    if (Junction_Right == True and Total_Junction == 5){ // at Junction 1
        Ignore_Turn = Ignore_Turn + 1;
        moveForward();
    }

    if (Junction_Zero == True and Total_Junction == 6 ) { // at Junction 0 return
        Pass_Zero = Pass_Zero + 1;
        TurnLeft(angles = 90);
        moveForward();
    }

    if (Junction_Zero == True and Total_Junction == 6 ) { // at the starting point
        if(Magnetic){
            TurnRight(angles = 90);
        }
        else{
            TurnLeft(angles = 90);
        }
        moveForward();
    }

    if (Junction_Five == True and Total_Junction == 7 ) { // at one of those colorful boxes
        Total_Junction = Total_Junction + 1;
        moveForward();
        delay(100);
        Stop();
        Reverse(delay = 2000);
        TurnLeft(angles = 180);
        moveForward();
    }

    if (Junction_Five == True and Total_Junction == 8 ) { // back in origin
        if(Magnetic){
            TurnLeft(angels = 90);
        }
        else{
            TurnRight(angles = 90);
        }
        Blocks = 1;
    }
}
}
Pass_Zero = 0;
Turn_Left_count = 0;
Turn_Right_count = 0;
Ignore_Turn = 0;
Total_Junction = Turn_Left_count + Turn_Right_count + Ignore_Turn + Pass_Zero;