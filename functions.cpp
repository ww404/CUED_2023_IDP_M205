void LineTracking(void){
    digitalWrite(led, HIGH);
    int valLeft_1 = digitalRead(leftlinesensorPin); // read left input value
    int valRight_1 = digitalRead(rightlinesensorPin); // read right input value

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

void MoveForward (void){
// This is going to be a function that 
// 1. moves forward while correcting the mistakes by calling TurnRight or TurnLeft
// 2. detects if there is a blck ahead and if so, calls function Block
    while (Found_Block == false){
        dist_t = sensity_t * MAX_RANG / ADC_SOLUTION ;
        Found_Block = (dist_t < 5);
        LineTracking();
    }
    Block();
}

// if angles = 90, then it turns exactly 90 degrees to the left or right
// else, it is correcting not following lines and turns until it is Straight again

void TurnLeft (int angles){
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(255*0.5); 
    Motor_R->setSpeed(255);
    delay(angles * 1850/90);  

}

void TurnRight (int angles){
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(255); 
    Motor_R->setSpeed(255*0.5);
    delay(angles * 1850/90);  
}


void Stop (){
    Motor_L->run(FORWARD);
    Motor_R->run(Forward);
    Motor_L->setSpeed(0); 
    Motor_R->setSpeed(0);
}

void Reverse (){
    Motor_L->run(Backward);
    Motor_R->run(Forward);
    Motor_L->setSpeed(255);
    Motor_R->spetSpeed(255);


}

void Block (int val_Ultra, int val_Mag){

    // Detects if the block is magnetic or not
    // Flashes the LED light
    // Clamps the clamp 

    Magnetic = digitalRead(MagInputPin);

    #define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
    #define ADC_SOLUTION (1023.0)//ADC accuracy of Arduino UNO is 10bit

    float distance_detected, block_distance;

    // read the value from the sensor:
    distance_detected = analogRead(ultrapin);
    block_distance = distance_detected * MAX_RANG / ADC_SOLUTION;
    if (block_distance <= 5){
        Jaws(closed);

        // Gemma's code
        int magnetic = 0; // variable for reading the pin status
        void setup() {
        pinMode(redPin, OUTPUT); // declare LED as output
        pinMode(greenPin, OUTPUT); // declare LED as output
        pinMode(inputPin, INPUT); // declare magnetic sensor as input

        magnetic = digitalRead(inputPin); // read input value
        if (val == HIGH) { // check if the input is HIGH
            digitalWrite(redPin, HIGH);
            digitalWrite(greenPin, LOW); // turn green LED on, red LED off
        } 
        
        else {
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, HIGH); // turn red LED on, green LED off
        }
}




    }

}

void Jaws(bool closed){
    #include <Servo.h>
    Servo myservo; // create servo object to control a servo

    int pos = 0; // variable to store the servo position
    myservo.attach(9); // attaches the servo on pin 9 to the servo object
    
    closed_angle = 180
    myservo.write(closed_angle); 
}

 

void Moving_Light
// flashes blue light when motors are moving
