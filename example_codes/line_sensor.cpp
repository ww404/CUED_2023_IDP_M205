int leftLineSensorPin = 2;
int rightLineSensorPin = 3; // Connect sensor to input pin 3
void setup() {
Serial.begin(9600); // Init the serial port
pinMode(leftLineSensorPin, INPUT); // declare LED as output
pinMode(rightLineSensorPin, INPUT); // declare Micro switch as input 
}
void loop(){
int valLeft = digitalRead(leftLineSensorPin); // read left input value
Serial.print(valLeft);
int valRight = digitalRead(rightLineSensorPin); // read right input value
Serial.println(valRight); delay(100);
}