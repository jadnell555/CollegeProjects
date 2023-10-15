// Author: Jadnell H. Reyes Perez #109739 
// COE 4341-23 (Microcomputer Interfacing) 
#define IN1  3 
#define IN2  4 
#define IN3  5 
#define IN4  6 
int Steps = 0; 
unsigned long last_time; 
unsigned long currentMillis ; 
int steps_leftCW=4095; 
int steps_leftCC=4095; 
long time; 
int flag = 0; 
int userStepsCW = 0; 
int userStepsCC = 0; 
  
void setup() 
{ 
Serial.begin(9600); 
pinMode(IN1, OUTPUT);  
pinMode(IN2, OUTPUT);  
pinMode(IN3, OUTPUT);  
pinMode(IN4, OUTPUT);  
// delay(1000); 
} 
void loop() 
{ 
  if(Serial.available() > 0){ 
    String option = Serial.readString(); 
    option.trim(); 
    Serial.println(option); 
    if (option == "CCC" || option == "ccc") 
      flag = 1; 
    else if (option == "CCW" || option == "ccw") 
      flag = 2; 
    else if (option == "CSC" || option == "csc"){ 
      flag = 3; 
      Serial.println("How many steps?"); 
      while(userStepsCW == 0){ 
      String userSteps = Serial.readString(); 
      userSteps.trim(); 
      userStepsCW = userSteps.toInt(); 
      } // end while 
      Serial.println("Steps: "); 
      Serial.println(userStepsCW); 
      delay(5000); 
    } // end else if 
    else if (option == "CSW" || option == "csw"){ 
      flag = 4; 
      Serial.println("How many steps?"); 
      while(userStepsCC == 0){ 
      String userSteps = Serial.readString(); 
      userSteps.trim(); 
      userStepsCC = userSteps.toInt(); 
      } // end while 
      Serial.println("Steps: "); 
      Serial.println(userStepsCC); 
      delay(5000); 
    } // end else if 
    else if (option == "STOP" || option == "stop") 
      flag = 5; 
    } // end if 
     
//Serial.println(flag); 
 
  switch (flag){ 
    case 0: 
      break; 
    case 1: 
       clockwiseContinuous(); 
       break; 
    case 2: 
      counterClockwiseContinuous(); 
      if(flag != 2) 
        break; 
    case 3: 
      clockwiseUserSteps(); 
      if(flag != 3) 
        break; 
    case 4: 
      counterClockwiseUserSteps(); 
      break; 
    case 5: 
      stopStepperMotor(); 
      if (flag != 5)  
        if(flag == 2){ 
          digitalWrite(IN1, HIGH);  
          digitalWrite(IN2, LOW); 
          digitalWrite(IN3, LOW); 
          digitalWrite(IN4, HIGH); 
          break; 
        } // end if 
        else  
          break; 
  } // end switch 
} // end loop() 
 
void clockwiseContinuous(){ 
  while(steps_leftCW>0) 
  { 
    currentMillis = micros(); 
    if(currentMillis-last_time>=1000) 
    { 
      stepper(Steps);  
      time=time+micros()-last_time; 
      last_time=micros(); 
      steps_leftCW--; 
    } // end if 
  } // end while 
  steps_leftCW=4095; 
} // end clockwiseContinuous() 
 
void clockwiseUserSteps(){ 
  while(userStepsCW>0) 
  { 
    currentMillis = micros(); 
    if(currentMillis-last_time>=1000) 
    { 
      stepper(Steps);  
      time=time+micros()-last_time; 
      last_time=micros(); 
      userStepsCW--; 
    } // end if 
  } // end while 
} // end clockwiseUserSteps() 
 
void counterClockwiseContinuous(){ 
  while(steps_leftCC>0) 
  { 
    currentMillis = micros(); 
    if(currentMillis-last_time>=1000) 
    { 
      stepperCC(Steps);  
      time=time+micros()-last_time; 
      last_time=micros(); 
      steps_leftCC--; 
    } // end if 
  } // end while 
  steps_leftCC=4095; 
} // end counterClockwiseContinuous() 
 
void counterClockwiseUserSteps(){ 
  while(userStepsCC>0) 
  { 
    currentMillis = micros(); 
    if(currentMillis-last_time>=1000) 
    { 
      stepperCC(Steps);  
      time=time+micros()-last_time; 
      last_time=micros(); 
      userStepsCC--; 
    } // end if 
  } // end while 
} // end counterClockwiseUserSteps() 
 
void stopStepperMotor(){ 
  digitalWrite(IN1, LOW);  
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, LOW); 
} // end stopStepperMotor 
 
//HALF Stepping switching Mode 
void stepper(int xw) 
  { 
   switch(xw) 
    { 
     case 0: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, HIGH); 
     break;  
     case 1: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, HIGH); 
     break;  
     case 2: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, LOW); 
     break;  
     case 3: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, LOW); 
     break;  
     case 4: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 5: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 6: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 7: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, HIGH); 
     break;  
     default: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
    } 
    Steps--; 
      if(Steps<0) 
        Steps=7; 
} 
 
void stepperCC(int xw) { 
   switch(xw) 
    { 
     case 0: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, HIGH); 
     break;  
     case 1: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 2: 
       digitalWrite(IN1, HIGH);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 3: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
     break;  
     case 4: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, HIGH); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, LOW); 
     break;  
     case 5: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, LOW); 
     break;  
     case 6: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, HIGH); 
       digitalWrite(IN4, HIGH); 
     break;  
     case 7: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, HIGH); 
     break;  
     default: 
       digitalWrite(IN1, LOW);  
       digitalWrite(IN2, LOW); 
       digitalWrite(IN3, LOW); 
       digitalWrite(IN4, LOW); 
       break;  
    } 
Steps--; 
  if(Steps<0) 
    Steps=7; 
} 