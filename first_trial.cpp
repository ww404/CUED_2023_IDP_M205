#include "functions.h"
// logic for junctions and normally turning
// functions we are using:
//      MoveForward     moves forward until deteects a block, and calls function Block
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

int valLeft = digitalRead(leftlinesensorPin); // read left input value
int valRight = digitalRead(rightlinesensorPin); // read right input value
int valCenter_left = digitalRead(centerlinesensorPin_left); 
int valCenter_right = digitalRead(centerlinesensorPin_right); 

// Actions:
//      boolean values:
Straight = (LineSensor_Left ==0, LineSensor_Right == 0, LineSensor_Center == 1)
Straight_Ignore = (LineSensor_Left == 0, LineSensor_Right == 0, LineSensor_Center == 0)
Leaning_Right = (LineSensor_Left == 1, LineSensor_Right == 0, LineSensor_Center == 0)
Leaning_Left = (LineSensor_Left == 0, LineSensor_Right == 1, LineSensor_Center == 0)
Junction_Left = (LineSensor_Left == 1, LineSensor_Right == 0, LineSensor_Center == 1)
Junction_Right = (LineSensor_Left == 0, LineSensor_Right == 1, LineSensor_Center == 1)
Junction_Zero = (LineSensor_Left ==1, LineSensor_Right == 1, LineSensor_Center == 1) 
//      Junction_Zero can also be the same as when turning back from junction five
Junction_Five = (LineSensor_Left ==1, LineSensor_Right == 1, LineSensor_Center == 0)

bool Found_Block, Magnetic;

// Junctions:
// Junction 5: Turn_Right_count ==0, Turn_Left_count ==0, Ignore_Turn == 0 and Junction_Five == true
// Junction 4: Turn_Right_count ==1, Turn_Left_count ==0, Ignore_Turn == 0 and Junction_Right == true
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
 while(Blocks == 0){

    if (Junction_Zero == True and Total_Junction == 0) {
        Pass_Zero = Pass_Zero + 1;
        MoveForward();
    }
          
    if (Junction_Five == True and Total_Junction == 1){ // at Junction 5
        TurnRight(angles = 90);
        Turn_Right_count = Turn_Right_count + 1;
        MoveForward();
    }

    if (Junction_Right == True and Total_Junction == 2){ // at Junction 4
        Ignore_Turn = Ignore_Turn + 1;
        MoveForward();
    }

    if (Junction_Right == True and Total_Junction == 3){ // at Junction 3
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(angles = 90);
        MoveForward();
    }

    if (Junction_Right == True and Total_Junction == 4){ // at Junction 2
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight(angles = 90);
        MoveForward();
    }

    if (Junction_Right == True and Total_Junction == 5){ // at Junction 1
        Ignore_Turn = Ignore_Turn + 1;
        MoveForward();
    }

    if (Junction_Zero == True and Total_Junction == 6 ) { // at Junction 0 return
        Pass_Zero = Pass_Zero + 1;
        TurnLeft(angles = 90);
        MoveForward();
    }

    if (Junction_Zero == True and Total_Junction == 6 ) { // at the starting point
        if(Magnetic){
            TurnRight(angles = 90);
        }
        else{
            TurnLeft(angles = 90);
        }
        MoveForward();
    }

    if (Junction_Five == True and Total_Junction == 7 ) { // at one of those colorful boxes
        Total_Junction = Total_Junction + 1;
        MoveForward();
        delay(100);
        Stop();
        Reverse(delay = 2000);
        TurnLeft(angles = 180);
        MoveForward();
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

Pass_Zero = 0;
Turn_Left_count = 0;
Turn_Right_count = 0;
Ignore_Turn = 0;
Total_Junction = Turn_Left_count + Turn_Right_count + Ignore_Turn + Pass_Zero;