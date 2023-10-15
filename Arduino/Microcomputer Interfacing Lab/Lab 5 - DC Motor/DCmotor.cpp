// Author: Jadnell H. Reyes Perez #109739 
// COE 4341-23 (Microcomputer Interfacing) 
// the setup function runs once when you press reset or power the board 
void setup() { 
pinMode(3, OUTPUT);  
pinMode(4, OUTPUT);  
Serial.begin(9600); 
} 
void loop() { 
/*Uncomment the desired Part Function since its not meant to have them 
runnning all at the same time nor its possible
*/

// Part I: Testing the DC Motor Works 
/*
clockwise(); 
delay(5000); 
counterClockwise(); 
delay(5000); 
off(); 
delay(5000); 
*/ 

// Part II: Incremeting the speed of the motor by 10% using PWM 
//  increment10Percent(); 
 
 
// Part III: Operate DC Motor with Keyboard Input 
//  MotorOperationKeyboard(); 

}  
 
// Make DC Motor turn clockwise 
void clockwise(){ 
  analogWrite(3, 255); 
  analogWrite(4, 0); 
} // end clockwise 
 
// Make DC Motor turn counter-clockwise 
void counterClockwise(){ 
  analogWrite(3, 0); 
  analogWrite(4, 255); 
} // end counterClockwise 
 
// Turn DC Motor Off 
void off(){ 
  analogWrite(3, 255); 
  analogWrite(4, 255); 
} // end off() 
 
//Increment DC Motor Speed by 10% every 10 seconds 
void increment10Percent(){ 
  float increment = 255 * .10; 
  float speed = 0.0; 
   
  for(int i = 0; i < 10; i++){ 
    analogWrite(3, 0); 
    analogWrite(4, speed); 
    delay(5000); 
    speed = speed + increment; 
  } // end for 
  speed = 0.0; 
  analogWrite(3, 255); 
  analogWrite(4, 255); 
  delay(10000); 
} // end increment10Percent() 
 
void MotorOperationKeyboard() { 
    while (Serial.available() == 0) 
    { 
      String optionCheck = Serial.readString(); 
      optionCheck.trim(); 
      if (optionCheck == "Turn On") 
        counterClockwise(); 
      else if (optionCheck == "Turn Off") 
        off(); 
      else if (optionCheck == "Motor CW") 
        clockwise(); 
else if (optionCheck == "Motor CC") 
counterClockwise(); 
} // end while 
} // end MotorOperationKeyboard 