
#define MAX_RANG (520)//the max measurement value of the module is 520cm(a little bit longer than effective max range)
#define  ADC_SOLUTION
int sensityPin = A0; void setup() {
  // Serial init
  Serial.begin(9600);
}
(1023.0)//ADC accuracy of Arduino UNO is 10bit // select the input pin
float dist_t, sensity_t;
void loop() {
// read the value from the sensor: sensity_t = analogRead(sensityPin);
// turn the ledPin on
dist_t = sensity_t * MAX_RANG / ADC_SOLUTION;// Serial.print(dist_t,0);
Serial.println("cm");
 delay(500);
}