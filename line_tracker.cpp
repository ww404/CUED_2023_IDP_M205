// function: track white lines and turn or keep followinging the line when there is a intersection


int leftlinesensorPin_1 = 2;
int rightlinesensorPin_1 = 3; // Connect sensor to input pin 3

int leftlinesensorPin_2 = 2;
int rightlinesensorPin_2 = 3; // Connect sensor to input pin 3

void setup() {
Serial.begin(9600); // Init the serial port
pinMode(leftlinesensorPin_1, INPUT); // declare LED as output
pinMode(rightlinesensorPin_1, INPUT); // declare Micro switch as input

pinMode(leftlinesensorPin_2, INPUT); // declare LED as output
pinMode(rightlinesensorPin_2, INPUT); // declare Micro switch as input 
}



void loop(){
int valLeft = digitalRead(leftlinesensorPin); // read left input value
// Serial.print(valLeft);
int valRight = digitalRead(rightlinesensorPin); // read right input value
// Serial.println(valRight); delay(100); // prinln starts a new line after the output

}