#include <Adafruit_MotorShield.h>
#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define  ADC_SOLUTION (1023.0)

int leftlinesensorPin = 2; 
int rightlinesensorPin = 3; 
int centerlinesensorPin_left = 4;
int centerlinesensorPin_right = 5;
int MagInputPin = 6;
int sensityPin = A3;
int greenLEDpin = 7;
int redLEDpin = 8;
int blueLEDpin = 9;


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Motor_L = AFMS.getMotor(1);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(2);



int valLeft = digitalRead(leftlinesensorPin); // read left input value
int valRight = digitalRead(rightlinesensorPin); // read right input value
int valCenter_left = digitalRead(centerlinesensorPin_left); 
int valCenter_right = digitalRead(centerlinesensorPin_right);
float sensity_t = analogRead(sensityPin);
float dist_t;

int Magnetic = digitalRead(MagInputPin);
int stop_LED = 0;

int speed = 180;



bool Found_Block;
bool Straight = (valLeft ==0 && valRight == 0);
bool Junction_Left = (valLeft == 1 && valRight == 0 && valCenter_left == 1 && valCenter_left == 1);
bool Junction_Right =  (valLeft == 0 && valRight == 1 && valCenter_left == 1 && valCenter_left == 1);
bool Junction_Zero = (valLeft == 1 && valRight == 1 && valCenter_left == 1 && valCenter_left == 1);
bool Junction_Five = (valLeft == 1 && valRight == 0 && valCenter_left == 0 && valCenter_left == 1);

int Pass_Zero, Blocks, Turn_Left_count, Turn_Right_count, Ignore_Turn, Total_Junction = Turn_Left_count + Turn_Right_count + Ignore_Turn + Pass_Zero;


void LineTracking(void){

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



if (valLeft == HIGH) {
    if (valRight == HIGH){
        TurnRight(90);
    }else {
        TurnLeft(90);
    }
    }
else if (valLeft == LOW and valRight == HIGH) {
    TurnRight(90);
}

}
    

void MoveForward(void){

  dist_t = sensity_t * MAX_RANG / ADC_SOLUTION;
  LineTracking();


  //if (dist_t < 5) {
  //  Block();
  //} 

  //else {
  //  LineTracking();
  //}
}
// if angles = 90, then it turns exactly 90 degrees to the left or right
// else, it is correcting not following lines and turns until it is Straight again

void TurnLeft (int angles){
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

void TurnRight (int angles){
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

void Reverse (){
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

  Magnetic = digitalRead(MagInputPin);

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
