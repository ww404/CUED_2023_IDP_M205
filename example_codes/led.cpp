int led = 2;
void setup() {
pinMode(led, OUTPUT);
}
void loop() {
//Set Pin3 as output
digitalWrite(led, HIGH); //Turn off led delay(2000);
digitalWrite(led, LOW); //Turn on led delay(2000);
}