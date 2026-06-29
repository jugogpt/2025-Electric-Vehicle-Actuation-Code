
//skibidi toliet code
// by hugo sanchez

//Pins that control direction of movement of the car
#define MotorDirPin1 9
#define MotorDirPin2 10

//Pin that control motor speed
#define MotorSpeedPin 11


volatile unsigned long counter = 0;  //This variable will increase or decrease depending on the rotation of encoder.


#define EncPinA 2 
#define EncPinB 3 


#define LaserPin 7
#define LaserButtonPin 5
int laser = 0;

#define StartButtonPin 8 

int start = 0;


double wheelDiameterCM = 5.08; // in cm




//REMEMBER TO CHECK YOUR GEARS + VARIABLES


//YOU ARE HERE :)

double targetDistanceM = 9.60; //Target Distance in m

double slowDownDistance = 5.10; //Distance where vehicle begins to slow down in m, multiply by 0.5 and NOT 3/7 3 sig figs
//if not specified, round up your calculation of slowDownDistance


int breakTimer = 100;
// REMEMBER TO TWIST THE TIRES TO HAVE GIVEEEEE

double pulsesPerRev = 104.5;

     //for 7.00, put 102.5 pulse, 200 break, timer 3.50, right on the black line, spank on
     //for 7.10, put 102.5, 200 break, timer 3.55, on the black line, but slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
     //for 7.20, put 102.5, 200 break, timer 3.60, on the black line, but slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
//for 7.25, put 101, 200 break, timer 3.11 
      //for 7.30, put 102.5, 200 break, timer 3.65, ever ever so slightly less right than the previous points, but still slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
      //for 7.40, put 102.5, 200 break timer 3.70, on the black line, but slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
      //for 7.50, put 102.5, 200 break, timer 3.75, on the black line, but slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
      //for 7.60, put 102.5, 200 break timer 3.80, on the black line, but slgihtly to the right so that the left red laser dot is on the black line, and the right one is barely not
       //for 7.70, put 102.6, 200 break, timer 3.85, right spank on the black line, ever so slihgly to the right
//for 7.75, put 99.5, 200 break, timer 3.85 
      //for 7.80, put 103, 100 break (yes change the break), timer 3.90, exactly right tangent, touching slighttly
      //for 7.90, put 103.3, 100 break, timer 3.95, right on the black line
      //for 8.00, put 103.7, 100 break, timer 4.00, right on the black line
      //for 8.10, put 103.7, 100 break, timer 4.05, right on the black line
      //for 8.20, put 103.7, q00 break, timer 4.10, right on the black line
//for 8.25, put 102.2, 200 break, 4.125 timer, 
     //for 8.30, put 103.7, 100 break, 4.15 timer, right on the black line
     //for 8.40, put 103.7, 100 break, 4.20 timer, right on the black line, slihgtly LEFT, inbetween white and black but still touching black
     //for 8.50, put 103.7, 100 break, 4.25 timer, right on the black line
     //for 8.60, put 103.7, 100 break, 4.30 timer, right on the black line
     //for 8.70, put 103.7, 100 break, 4.35 timer, right inbetween the black line and the white line, more towards the black
//for 8.75, put 103, break 200, timer 4.375,
     //for 8.80, put 103.7, break 100, timer 4.40, right inbetween the two white lines, slightly to the left if anything
     //for 8.90, put 103.7, break 100, timer 4.45, right inbetween the two white lines, slightly to the left if any skew
     //for 9.00, put 103.7, break 200, timer 4.5, right spank on the black line
     //for 9.10, put 103.2, break 200, timer 4.55, right tangent to the black line, still touching though
//for 9.25, put 102.2, break 200, timer 4.625, right tangent to the black line, still touching though
     //for 9.20, put 103.2, break 200, timer 4.60, right tangent to the black line, still touching though
     //for 9.30, put 103.7, break 200, timer 4.65, right tangent to the black line, still touching though
     //for 9.40, put 103.3, break 200, timer 4.70, RIGHT SPANK ON THE BLACK LINE YESSUAH
     //for 9.50, put 103.3, break 200, timer 4.75, IGHT SPANK ON THE BLACK LINE YESSUAH
     //for 9.60, put 104.5, break 200, timer 4.80, right on the black line, right head on
     //for 9.70, put 104.55, break 100, timer 4.85, on black line, right head on
//for 9.75, put 102.2, break 200, timer 5.28,
     //for 9.80, put 103.7, break 100, timer 5.20, on the furthest white line
     //for 9.90, put 103.7, break 100, timer 5.20, on black line, in between the two white lines
     //for 10.00,put 103.7, break 100, timer 5.40, in between the two white lines





double targetDistEncVal;
double slowDownDistEncVal; 


int vehicleMoved = 0;
int vehicleSlowedDown = 0;
int vehicleReachedTargetDistance = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); //Starts Serial Monitor

  //Initalize motor pins
  pinMode(MotorDirPin1, OUTPUT);
  pinMode(MotorDirPin2, OUTPUT);
  pinMode(MotorSpeedPin, OUTPUT);

  //Initalize Encoder pins
  pinMode(EncPinA, INPUT);
  pinMode(EncPinB, INPUT);
  digitalWrite(EncPinA, HIGH); // turn on pullup resistors
  digitalWrite(EncPinB, HIGH); // turn on pullup resistors

  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);

  //Initalize button pins
  pinMode(StartButtonPin, INPUT);
  digitalWrite(StartButtonPin, HIGH); 

  pinMode(LaserButtonPin, INPUT);
  digitalWrite(LaserButtonPin, HIGH); 

  //Initalize Laser pins
  pinMode(LaserPin, OUTPUT);
  digitalWrite(LaserPin, LOW);

  
  start = 0;
  vehicleMoved = 0;
  vehicleSlowedDown = 0;
  vehicleReachedTargetDistance = 0;
  laser = 0;

  
  targetDistEncVal = getEncoderValue (targetDistanceM, wheelDiameterCM, pulsesPerRev);
  slowDownDistEncVal = getEncoderValue (slowDownDistance, wheelDiameterCM, pulsesPerRev);

}

void loop() {
  

  if (digitalRead(LaserButtonPin) == LOW){
      if(laser == 0){
        Serial.println("Laser On");
        digitalWrite(LaserPin, HIGH);
        laser = 1;
        delay (300);
      }
      else{
        Serial.println("Laser Off");
        digitalWrite(LaserPin, LOW);
        laser = 0;
        delay (breakTimer);
      }
  }

  if (digitalRead(StartButtonPin) == LOW){
      Serial.println("pressed");
      Serial.println(targetDistEncVal);
      Serial.println(slowDownDistEncVal);
      counter = 0;
      vehicleMoved = 0;
      vehicleSlowedDown = 0;
      vehicleReachedTargetDistance = 0;
      start = 1;
  }

  if (start == 1){
    Serial.println("start");
    digitalWrite(MotorDirPin1, HIGH);
    digitalWrite(MotorDirPin2, LOW);
    analogWrite(MotorSpeedPin, 255); 
    vehicleMoved = 1;
    start = 0;
  }

  if (vehicleMoved == 1){
    if (counter >= slowDownDistEncVal && counter < targetDistEncVal){
      
    
      analogWrite(MotorSpeedPin, 0); // Turn off Motor
      vehicleSlowedDown = 1;
      vehicleMoved = 0;
    }
  }

  if (vehicleSlowedDown == 1){
    if(counter >= targetDistEncVal){
      Serial.println("DONE");
      analogWrite(MotorSpeedPin, 0);
      //Reverse motor direction for 300 ms to stop vehicle
      digitalWrite(MotorDirPin1, LOW);
      digitalWrite(MotorDirPin2, HIGH);
      //Set motor speed
      analogWrite(MotorSpeedPin, 255); //(0  = off and 255 = max speed)
      delay(300);
      analogWrite(MotorSpeedPin, 0); //(0  = off and 255 = max speed)
      vehicleReachedTargetDistance = 1;
      vehicleSlowedDown = 0;
    }
  
  }

  if (vehicleReachedTargetDistance == 1){
    //Reset variables
    Serial.println(counter);
    counter = 0;
    vehicleMoved = 0;
    vehicleSlowedDown = 0;
    vehicleReachedTargetDistance = 0;
    start = 0;
  }

}


void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
    counter++;
  }else{
    counter--;
  }
}

void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
    counter--;
  }else{
    counter++;
  }
}


double getEncoderValue (double targetDistanceM, double WD, double PR){
    double WheelCircumfrence = 3.14159 * WD;
    double tgtENCval = ((targetDistanceM * 100) / WheelCircumfrence) * PR;
    return tgtENCval;
  }

