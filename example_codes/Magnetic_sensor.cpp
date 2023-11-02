int ledPin = 13;
int inputPin = 2;
int val = 0;
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}
void loop(){
  val = digitalRead(inputPin);
  if (val == HIGH) {
// choose the pin for the LED
// choose the input pin
// variable for reading the pin status
// declare LED as output
// declare pushbutton as input
// read input value
                            // check if the input is HIGH
digitalWrite(ledPin, LOW);  // turn LED OFF
} else {
  digitalWrite(ledPin, HIGH); // turn LED ON
} }