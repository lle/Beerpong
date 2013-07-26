#include <Servo.h> 

//Input Potentiometer
int pinPotentio = A0;
int potentioMin = 175;
int potentioMax = 1023;
//Inputs Button
int pinButtonFire = A1;
int pinButtonMotor1 = A2;
int pinButtonMotor2 = A3;
//Output pin to H-Bridge for Motor
int pinMotorOut1 = 2;
int pinMotorOut2 = 3;
int pinPwmMotor = 5;
int motorPwm = 196;
//Output pin to H-bridge for Solenoid
int pinSolenoidOut1 = 4;
int pinSolenoidOut2 = 7;
//Servo Motors
int pinServoArm = 6;
Servo servoArm;  // create servo object to control a servo 
int servoArmMin = 0;
int servoArmMax = 90;

//Global Variable
int servoVal = 0;
int knobVal = 0;
 
void arming()    //Arming Sequence
{
  Serial.println("Arming");
  //Unlock Solenoid
  digitalWrite(pinSolenoidOut1, HIGH);
  digitalWrite(pinSolenoidOut2, LOW);
  delay(1000);
  //Lower Arm
  servoArm.write(0);
  delay(250);
  //Lock Solenoid
  digitalWrite(pinSolenoidOut1, LOW);
  digitalWrite(pinSolenoidOut2, LOW);
  delay(1500);
  //Rise Arm
  //Charge and ready to fire
  servoArm.write(45);  
  Serial.println("Armed");
}
 
void setup() 
{  
  Serial.begin(9600);
  Serial.println("Setup in progress\n");
  
  Serial.println(" -> Set Button->Fire");
  //Setup Input Button for Firing
  pinMode(pinButtonFire, INPUT);
  digitalWrite(pinButtonFire, HIGH);
  
  Serial.println(" -> Set Button->Motor");
  //Setup Motor input button
  pinMode(pinButtonMotor1, INPUT);
  pinMode(pinButtonMotor2, INPUT);
  digitalWrite(pinButtonMotor1, HIGH);
  digitalWrite(pinButtonMotor2, HIGH);
  Serial.println(" -> Set Hbridge->Motor");
  //Setup motor output
  pinMode(pinMotorOut1, OUTPUT);
  pinMode(pinMotorOut2, OUTPUT);
  digitalWrite(pinMotorOut1, LOW);
  digitalWrite(pinMotorOut2, LOW);
  
  Serial.println(" -> Set Hbridge->Motor PWM");
  pinMode(pinPwmMotor, OUTPUT);
  analogWrite(pinPwmMotor, motorPwm);
  
  Serial.println(" -> Set Hbridge->Solenoid");
  //Setup Solenoid
  pinMode(pinSolenoidOut1, OUTPUT);
  pinMode(pinSolenoidOut2, OUTPUT);
  
  //Setup Servo
  Serial.println(" -> Set Servo->Arm\n");
  servoArm.attach(pinServoArm);  // attaches the servo on pin 9 to the servo object  
  
  //Arming
  Serial.println("Setup Mechanism");
  arming();
  
  Serial.println("Program Start");
} 
 
void loop() 
{ 
  //Update Tower Rotation
  while(digitalRead(pinButtonMotor1) == LOW)
  {
    digitalWrite(pinMotorOut1, HIGH);
    digitalWrite(pinMotorOut2, LOW);
    Serial.println("Motor Button 1 Pressed");
  }
  while(digitalRead(pinButtonMotor2) == LOW)
  {
    digitalWrite(pinMotorOut1, LOW);
    digitalWrite(pinMotorOut2, HIGH);
    Serial.println("Motor Button 2 Pressed");
  }
  digitalWrite(pinMotorOut1, LOW);
  digitalWrite(pinMotorOut2, LOW);
  
  //Check if Fire
  if(digitalRead(pinButtonFire) == LOW)
  {
    Serial.println("Fire!");
    digitalWrite(pinSolenoidOut1, HIGH);
    digitalWrite(pinSolenoidOut2, LOW);
    delay(500);
    digitalWrite(pinSolenoidOut1, LOW);
    digitalWrite(pinSolenoidOut2, LOW);
    delay(500);
    arming();
    delay(500);
  }
  
  //Update Servo Position
  knobVal = analogRead(pinPotentio);
  //Serial.print(knobVal);
  //Serial.print(" = ");
  servoVal = map(knobVal, potentioMin, potentioMax, servoArmMax, servoArmMin);     // scale it to use it with the servo (value between 0 and 180) 
  //Serial.println(servoVal);
  servoArm.write(servoVal);
  
  delay(50);                           // waits for the servo to get there 
}
