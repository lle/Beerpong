#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 

int servoVal = 0;
int knobVal = 0;
 
void arming()    //Arming Sequence
{
  //Unlock Solenoid
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  delay(1000);
  //Lower Arm
  myservo.write(0);
  delay(250);
  //Lock Solenoid
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  delay(1500);
  //Rise Arm
  //Charge and ready to fire
  myservo.write(45);  
}
 
void setup() 
{  
  //Setup Input Button for Firing
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
  
  //Setup Motor input button
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  //Setup motor output
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  
  //Setup Solenoid
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  //Arming
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object  
  arming();
} 
 
void loop() 
{ 
  //Update Tower Rotation
  while(digitalRead(7) == LOW)
  {
    digitalWrite(1, HIGH);
    digitalWrite(0, LOW);
  }
  while(digitalRead(6) == LOW)
  {
    digitalWrite(1, LOW);
    digitalWrite(0, HIGH);
  }
  digitalWrite(1, LOW);
  digitalWrite(0, LOW);
  
  //Check if Fire
  if(digitalRead(5) == LOW)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    delay(500);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    delay(500);
    arming();
    delay(500);
  }
  
  //Update Servo Position
  knobVal = analogRead(0);
  servoVal = map(knobVal, 0, 1023, 0, 90);     // scale it to use it with the servo (value between 0 and 180) 
  myservo.write(servoVal);
  
  delay(50);                           // waits for the servo to get there 
}
