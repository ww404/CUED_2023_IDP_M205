void MoveForward (int val_Left, int val_Right){
// This is going to be a function that 
// 1. moves forward while correcting the mistakes by calling TurnRight or TurnLeft
// 2. detects if there is a blck ahead and if so, calls function Block


    Motor_L->run(RELEASE);
    Motor_R->run(RELEASE);



    if (valLeft == HIGH) {
        Motor_L->run(Forward);
        Motor_R->run(Backward);
        Motor_R->setSpeed(255);
        Motor_L->spetSpeed(127);
        Delay(100);

        //Again modify the delay as required to achieve a suitable amount of rotation
    }

    else if (valRight == HIGH) {
        Motor_L->run(Forward);
        Motor_R->run(Backward);
        Motor_L->setSpeed(255);
        Motor_R->spetSpeed(127);
        Delay(100);

        // Same as above
    }

    else {
        Motor_L->run(Forward);
        Motor_R->run(Backward);
        Motor_L->setSpeed(255);
        Motor_R->spetSpeed(255);
    }

}

// if angles = 90, then it turns exactly 90 degrees to the left or right
// else, it is correcting not following lines and turns until it is Straight again

void TurnLeft (int angles){
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(255*0.54*0.5); //Using 50/20 rmp motor correction
    Motor_R->setSpeed(255);
    delay(angles * 1850/90);  

}

void TurnRight (int angles){
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(255*0.54); //Using 50/20 rmp motor correction
    Motor_R->setSpeed(255*0.5);
    delay(angles * 1850/90);  
}


void Stop (){
    Motor_L->run(FORWARD);
    Motor_R->run(Forward);
    Motor_L->setSpeed(0); //Using 50/20 rmp motor correction
    Motor_R->setSpeed(0);
}

void Reverse (){
    Motor_L->run(Backward);
    Motor_R->run(Forward);
    Motor_L->setSpeed(255);
    Motor_R->spetSpeed(255);


}

void Block (int val_Ultra, int val_Mag){

    // Detecting a 
    // Detects if the block is magnetic or not
    // Flashes the LED light
    // Clamps the clamp 



}
 

void Moving_Light
// flashes blue light when motors are moving
