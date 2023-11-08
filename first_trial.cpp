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

// Junctions:
// Junction 5: Turn_Right_count ==0, Turn_Left_count ==0, Ignore_Turn == 0 and Junction_Five == True
// Junction 4: Turn_Right_count ==1, Turn_Left_count ==0, Ignore_Turn == 0 and Junction_Right == True
// Junction 3: Turn_Right_count ==1, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == True
// Junction 2: Turn_Right_count ==2, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == True
// Junction 1: Turn_Right_count ==3, Turn_Left_count ==0, Ignore_Turn == 1 and Junction_Right == True

// counts
Pass_Zero = 0;
Blocks = 0;
Turn_Left_count = 0;
Turn_Right_count = 0;
Ignore_Turn = 0;

// What is going to happen IDEALLY:
 while(not Straight and not Straight_Ignore){

    if (Junction_Zero == True) {
        Pass_Zero = Pass_Zero + 1
        MoveForward;
    }
          
    if (Junction_Five == True){
        TurnRight(angles = 90);
        Turn_Right_count = Turn_Right_count + 1;
        MoveForward;
    }

    if (Junction_Right == True){
        Ignore_Turn = Ignore_Turn + 1
        MoveForward;
    }

    if (Junction_Right == True){
        Turn_Right_count = Turn_Right_count + 1;
        TurnRight;
        MoveForward;
    }
    Junction_Right == True
    MoveForward

}
