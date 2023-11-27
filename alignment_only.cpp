#include <Adafruit_MotorShield.h> // FORWARD = 1; BACKWARD = 2
#define MAX_RANG (520) // the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define ADC_SOLUTION (1023.0)

// Pin allocation
const int fllsPin = 2; // far left line sensor
const int frlsPin = 3; // far right ls
const int cllsPin = 4; // centre left ls
const int crlsPin = 5; // centre right ls
const int magPin = 6;  // Hall effect sensor
const int usPin = A3;  // Ultrasonic
const int greenLedPin = 7;
const int redLedPin = 8;
const int blueLedPin = 9;
const int buttonPin = 10;

int retrivalcounter = 0;
int buttonCounter;
int alignCount = 0;

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
const int slowerSpeed = (int) speed / 1.7;
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

void MoveForward(int speed = speed)
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
  int cllsVal = digitalRead(cllsPin);
  int crlsVal = digitalRead(crlsPin);
  int fllsVal = digitalRead(fllsPin);
  Motor_L->run(BACKWARD);
  Motor_R->run(FORWARD);
  Motor_L->setSpeed(corner_speed);
  Motor_R->setSpeed(corner_speed);
  delay(1500);

  cllsVal = digitalRead(cllsPin);
  crlsVal = digitalRead(crlsPin);

  while (crlsVal == LOW || cllsVal == HIGH)
  {
    cllsVal = digitalRead(cllsPin);
    crlsVal = digitalRead(crlsPin);
    Motor_L->run(BACKWARD);
    Motor_R->run(FORWARD);
    Motor_L->setSpeed(corner_speed);
    Motor_R->setSpeed(corner_speed);
  }

  while (cllsVal == LOW || crlsVal == LOW)
  {
    cllsVal = digitalRead(cllsPin);
    crlsVal = digitalRead(crlsPin);

    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_R->setSpeed(speed * 0.4);
    Motor_L->setSpeed(speed);
  }
}

void TurnRight()
{
  int cllsVal = digitalRead(cllsPin);
  int crlsVal = digitalRead(crlsPin);
  int corner_speed = 120;
  int speed = 180;

  Motor_L->run(FORWARD);
  Motor_R->run(BACKWARD);
  Motor_L->setSpeed(corner_speed);
  Motor_R->setSpeed(corner_speed);
  delay(1000);

  cllsVal = digitalRead(cllsPin);
  crlsVal = digitalRead(crlsPin);

  while (cllsVal == LOW || crlsVal == HIGH)
  {
    cllsVal = digitalRead(cllsPin);
    crlsVal = digitalRead(crlsPin);
    Motor_L->run(FORWARD);
    Motor_R->run(BACKWARD);
    Motor_L->setSpeed(corner_speed);
    Motor_R->setSpeed(corner_speed);
  }

  while (cllsVal == LOW || crlsVal == LOW)
  {
    cllsVal = digitalRead(cllsPin);
    crlsVal = digitalRead(crlsPin);
    Motor_L->run(FORWARD);
    Motor_R->run(FORWARD);
    Motor_R->setSpeed(speed);
    Motor_L->setSpeed(speed * 0.4);
  }
}

void alignTurn(int turnTime)  // turn right if turnTime < 0, vice versa
{
  // Private variables declaration
  int ldir = 1; // left motor direction
  int rdir = 0; // right motor direction

  reverse(slowerSpeed);
  delay(70);
  stop();
  if (turnTime == 0) {return;}  // return if turntime == 0.
  ldir = 1 + (turnTime > 0);
  rdir = 1 + (turnTime < 0);
  Motor_L->run(ldir);
  Motor_R->run(rdir);
  delay(abs(turnTime));
  stop();

  // Reset the speeds
  Motor_L->setSpeed(speed);
  Motor_R->setSpeed(speed);
}

void stop()
{
  Motor_L->run(BRAKE);
  Motor_R->run(BRAKE);
}

void reverse(int speed)
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
    pinMode(buttonPin, INPUT);
  }
}


void loop()
{
  // put your main code here, to run repeatedly:
  // Read sensors, put it here so you don't have to repeatedly code this
  int button = digitalRead(buttonPin);
  int cllsVal = digitalRead(cllsPin);
  int crlsVal = digitalRead(crlsPin);
  int fllsVal = digitalRead(fllsPin); // read left input value
  int frlsVal = digitalRead(frlsPin); // read right input value
  float usVal = analogRead(usPin);
  bool magDetected = digitalRead(magPin);
  int usDistance = usVal * MAX_RANG / ADC_SOLUTION;
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
    buttonCounter = 1;
    // junctioncounter = 1;

    return;
  }

  // Block Detection
  if (buttonCounter == 1)
  {
    if ((usDistance <= 4) && (!pickedUp))
    {
      pickedUp = true;
      if (magDetected == HIGH)
      { // check if the input is HIGH
        digitalWrite(redLedPin, HIGH);
        magnetic = true;
        stop();
        delay(6000);
        digitalWrite(redLedPin, LOW); // turn red LED on
                                      // willprob need to put a counter in this to make it go a second time ie when counter = 1 and pickup = true
        return;
      }
      else
      {
        digitalWrite(greenLedPin, HIGH);
        stop();
        delay(6000);
        magnetic = false;
        digitalWrite(greenLedPin, LOW); // turn green LED on
        return;
      }
    }

    // second attempt at junctions
    Serial.print("fllsVal, frlsVal = ");
    Serial.print(fllsVal);
    Serial.println(frlsVal);
    Serial.println();


    // Align with the line
    if (fllsVal == 0 && frlsVal == 0)
    {
      alignCount = 0;
      MoveForward(slowerSpeed);
      delay(100);
      Serial.println("00");
    } else if (fllsVal == 1 && frlsVal == 0) {
      alignTurn(250 * pow(0.95, alignCount));
      Serial.println("10");
      alignCount ++;
    } else if (fllsVal == 0 && frlsVal == 1) {
      alignTurn(-250 * pow(0.95, alignCount));
      Serial.println("01");
      alignCount ++;
    } else {
      MoveForward(255);
      delay(5000);
      Serial.println("11");
      alignCount = 0;   // reset alignCount
    }
  }
  else
  {
    MoveForward();
  }
}
