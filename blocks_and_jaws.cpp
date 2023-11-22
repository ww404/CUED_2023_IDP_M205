
int Block(){

  // Detects if the block is magnetic or not
  // Flashes the LED light
  // Clamps the clamp 

  Magnetic = digitalRead(magInputPin);

  float block_distance;

  // read the value from the sensor:
  sensity_t = analogRead(sensityPin);
  block_distance = sensity_t * MAX_RANG / ADC_SOLUTION;
  if (block_distance <= 5){
    Jaws(closed = true);

    if (block_distance <= 1) {

     // Gemma's code
        
      if (stop_LED == 0) {
        int magnetic = 0; // variable for reading the pin status
        
        if (magnetic == HIGH) { // check if the input is HIGH
          digitalWrite(redLEDpin, HIGH);
          delay(6000);
          digitalWrite(redLEDpin, LOW); // turn red LED on
          stop_LED = 1;
        }  
                
        else {
          digitalWrite(greenLEDpin, HIGH);
          delay(6000); 
          digitalWrite(greenLEDpin, LOW);// turn green LED on
          stop_LED = 1;
       }

       stop_LED = 1;
      } 
    }
         
  }   

}



int Jaws(bool closed){
    #include <Servo.h>
    Servo myservo; // create servo object to control a servo

    int pos = 0; // variable to store the servo position
    myservo.attach(9); // attaches the servo on pin 9 to the servo object

    int closed_angle;
    if (closed){
        closed_angle = 180;
    }else {
        closed_angle = 0;
    }
    
    myservo.write(closed_angle); 
}
