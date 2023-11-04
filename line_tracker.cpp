// function: track white lines and turn or keep followinging the line when there is a intersection


int leftlinesensorPin_1 = 2;
int rightlinesensorPin_1 = 3; // Connect sensor to input pin 3

int leftlinesensorPin_2 = 4;
int rightlinesensorPin_2 = 5; // Connect sensor to input pin 3


// defining functions here

// this is a function telling it to move forward until line detector notices smth different

void TurnLeft (bool left){
    while (left) {
  uint8_t i;

  myMotor->run(FORWARD);
  myOtherMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(255*0.3);
    myOtherMotor->setSpeed(255);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(255*0.3);
    myOtherMotor->setSpeed(255);
    delay(10);
  }
    }
}


// turning left 
void MoveForward (bool stop){
    while (!stop) {
  uint8_t i;

  myMotor->run(FORWARD);
  myOtherMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(255);
    myOtherMotor->setSpeed(255);
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(255);
    myOtherMotor->setSpeed(255);
    delay(10);
  }
    }
}



void setup() {



// setup for line_sensors
Serial.begin(9600); // Init the serial port
pinMode(leftlinesensorPin_1, INPUT); // declare LED as output
pinMode(rightlinesensorPin_1, INPUT); // declare Micro switch as input

pinMode(leftlinesensorPin_2, INPUT); // declare LED as output
pinMode(rightlinesensorPin_2, INPUT); // declare Micro switch as input 





// copying the setup for motors
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(60);
  myOtherMotor->setSpeed(150);
  myMotor->run(FORWARD);
  myOtherMotor->run(BACKWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myOtherMotor->run(RELEASE);

}



void loop(){
int valLeft_1 = digitalRead(leftlinesensorPin_1); // read left input value
int valLeft_2 = digitalRead(leftlinesensorPin_2); 
// Serial.print(valLeft_1);
int valRight_1 = digitalRead(rightlinesensorPin_1); // read right input value
int valRight_2 = digitalRead(rightlinesensorPin_2); 
// Serial.println(valRight_1); delay(100); // prinln starts a new line after the output

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
}