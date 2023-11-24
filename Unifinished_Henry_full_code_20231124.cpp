#include <Adafruit_MotorShield.h>
#define MAX_RANG (520) // the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)

// Pin allocation
const int fllsPin = 2;   // far left line sensor
const int frlsPin = 3;   // far right ls
const int cllsPin = 4;  // centre left ls
const int crlsPin = 5;  // centre right ls
const int magPin = 6;   // Hall effect sensor
const int usPin = A3;   // Ultrasonic
const int greenLedPin = 7;
const int redLedPin = 8;
const int blueLedPin = 9;
const int buttonPin = 10;

int retrivalcounter = 0;

// Motor setup
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *Motor_L = AFMS.getMotor(2);
Adafruit_DCMotor *Motor_R = AFMS.getMotor(1);

// Global variables
bool pickedUp = false;
bool magnetic = false;

// For flashing the blue led
const long flash_interval = 250;
unsigned long previousMillis = 0;
unsigned long currentMillis;
int ledState = LOW;

// For junction counting
int junctioncounter = 0;
bool reachedJunction0 = false;
const int speed = 180; // risky = may want to calibrate to speed
const int corner_speed = 120;


void CorrectRight()
{
  Motor_L->run(FORWARD);
  Motor_R->run(FORWARD);
  Motor_L->setSpeed(speed * 0.8);
  Motor_R->setSpeed(speed);
  if (currentMillis - previousMillis >= flash_interval)
  {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(blueLedPin, ledState);
  }
  return;
}

void CorrectLeft()
{
  Motor_L->run(FORWARD);
  Motor_R->run(FORWARD);
  Motor_R->setSpeed(speed * 0.8); // may have to lower this
  Motor_L->setSpeed(speed);
  if (currentMillis - previousMillis >= flash_interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    ledState = !ledState;

    // set the LED with the ledState of the variable:
    digitalWrite(blueLedPin, ledState);
    return;
  }
}

void MoveForward()
{
  Motor_L->run(FORWARD);
  Motor_R->run(FORWARD);
  Motor_R->setSpeed(speed);
  Motor_L->setSpeed(speed);
  if (currentMillis - previousMillis >= flash_interval)
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    ledState = !ledState;


    // set the LED with the ledState of the variable:
    digitalWrite(blueLedPin, ledState);
    return;
  }
}

void TurnLeft()
{
  int valCenter_left = digitalRead(cllsPin);
  int valCenter_right = digitalRead(crlsPin);
  int valLeft = digitalRead(fllsPin);
  Motor_L->run(BACKWARD);
  Motor_R->run(FORWARD);
  Motor_L->setSpeed(corner_speed);
  Motor_R->setSpeed(corner_speed);
  delay(1500);

  valCenter_left = digitalRead(cllsPin);
  valCenter_right = digitalRead(crlsPin);

  while (valCenter_right == LOW || valCenter_left == HIGH)
  {
    valCenter_left = digitalRead(cllsPin);
    valCenter_right = digitalRead(crlsPin);
    Motor_L->run(BACKWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(corner_speed);
    Motor_R->setSpeed(corner_speed);
  }

  while (valCenter_left == LOW || valCenter_right == LOW)
  {
    valCenter_left = digitalRead(cllsPin);
    valCenter_right = digitalRead(crlsPin);

    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_R->setSpeed(speed * 0.4);
    Motor_L->setSpeed(speed);
  }
}

void TurnRight()
{
  int valCenter_left = digitalRead(cllsPin);
  int valCenter_right = digitalRead(crlsPin);
  int corner_speed = 120;
  int speed = 180;

  Motor_L->run(FORWARD);
  Motor_R->run(BACKWARD);
  Motor_L->setSpeed(corner_speed);
  Motor_R->setSpeed(corner_speed);
  delay(1000);

  valCenter_left = digitalRead(cllsPin);
  valCenter_right = digitalRead(crlsPin);

  while (valCenter_left == LOW || valCenter_right == HIGH)
  {
    valCenter_left = digitalRead(cllsPin);
    valCenter_right = digitalRead(crlsPin);
    Motor_L->run(FORWARD);
    Motor_R->run(BACKWARD);
    Motor_L->setSpeed(corner_speed);
    Motor_R->setSpeed(corner_speed);
  }

  while (valCenter_left == LOW || valCenter_right == LOW)
  {
    valCenter_left = digitalRead(cllsPin);
    valCenter_right = digitalRead(crlsPin);
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_R->setSpeed(speed);
    Motor_L->setSpeed(speed * 0.4);
  }
}

void Stop()
{
  Motor_L->run(FORWARD);
  Motor_R->run(FORWARD);
  Motor_L->setSpeed(0);
  Motor_R->setSpeed(0);
}

void Reverse(int speed)
{
  Motor_L->run(BACKWARD);
  Motor_R->run(BACKWARD);
  Motor_L->setSpeed(speed);
  Motor_R->setSpeed(speed);
}



void setup()
{
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin())
  { // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1)
      ;
    // Set the speed to start, from 0 (off) to 255 (max speed)
    Motor_R->setSpeed(255);
    Motor_L->setSpeed(255);
    Motor_R->run(FORWARD);
    Motor_L->run(FORWARD);
    // turn on motor
    Motor_R->run(RELEASE);
    Motor_L->run(RELEASE);

    pinMode(fllsPin, INPUT);
    pinMode(frlsPin, INPUT);
    pinMode(cllsPin, INPUT);
    pinMode(crlsPin, INPUT);

    pinMode(magPin, INPUT);
    pinMode(usPin, INPUT);
    pinMode(greenLedPin, OUTPUT);
    pinMode(redLedPin, OUTPUT);
    pinMode(blueLedPin, OUTPUT);
    pinMode(buttonpin, INPUT);
  }
}
void loop()
{
  // put your main code here, to run repeatedly:
  // Read sensors, put it here so you don't have to repeatedly code this
  int button = digitalRead(buttonpin);
  int valCenter_left = digitalRead(cllsPin);
  int valCenter_right = digitalRead(crlsPin);
  int valLeft = digitalRead(fllsPin);   // read left input value
  int valRight = digitalRead(frlsPin); // read right input value
  float sensity_t = analogRead(usPin);
  bool Magnetic = digitalRead(magPin);
  int block_distance = sensity_t * MAX_RANG / ADC_SOLUTION;
  unsigned long currentMillis = millis();

  if (button == HIGH)
  {
    MoveForward();
    currentMillis = millis();
    Serial.println(currentMillis);
    if (currentMillis - previousMillis >= flash_interval)
    {
      // save the last time you blinked the LED
      previousMillis = currentMillis;

      // if the LED is off turn it on and vice-versa:
    ledState = !ledState;


      // set the LED with the ledState of the variable:
      digitalWrite(blueLedPin, ledState);
    }
    delay(1000);
    buttoncounter = 1;
    // junctioncounter = 1;

    return;
  }

  // Block Detection
  if (buttoncounter == 1)
  {
    if ((block_distance <= 4) && (!pickedUp))
    {
      pickedUp = true;
      if (Magnetic == HIGH)
      { // check if the input is HIGH
        digitalWrite(redLedPin, HIGH);
        magnetic = true;
        Stop();
        delay(6000);
        digitalWrite(redLedPin, LOW); // turn red LED on
                                      // willprob need to put a counter in this to make it go a second time ie when counter = 1 and pickup = true
        return;
      }
      else
      {
        digitalWrite(greenLedPin, HIGH);
        Stop();
        delay(6000);
        magnetic = false;
        digitalWrite(greenLedPin, LOW); // turn green LED on
        return;
      }
    }

    // second attempt at junctions

    if (valLeft == 1 || valRight == 1)
    {
      if (junctioncounter == 0)
      {
        MoveForward();
        junctioncounter++;
        delay(200);
      }
      else if (junctioncounter == 1)
      {
        TurnRight();
        junctioncounter++;
        MoveForward();
        delay(200);
      }
      else if (junctioncounter == 2)
      {
        MoveForward();
        junctioncounter++;
        delay(200);
      }
      else if (junctioncounter == 3)
      {
        TurnRight();
        junctioncounter++;
        MoveForward();
        delay(200);
      }
      else if (junctioncounter == 4)
      {
        TurnRight();
        junctioncounter++;
        MoveForward();
        delay(200);
      }
      else if (junctioncounter == 5)
      {
        MoveForward();
        junctioncounter++;
        delay(200);
      }
      else if (junctioncounter == 6)
      {
        TurnLeft();
        junctioncounter++;
        delay(200);
      }

      // line following
      else if (valCenter_left == 1 && valCenter_right == 0)
      {
        CorrectRight();
      }
      else if (valCenter_left == 0 && valCenter_right == 1)
      {
        CorrectLeft();
      }
      else if (junctioncounter == 7 && valCenter_left == 0 && valCenter_right == 0)
      {
        delay(500);
      }
    }
    else
    {
      MoveForward();
    }

    // Serial.println(block_distance);
    return;
  }
}
