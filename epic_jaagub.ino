#include <Servo.h>

const int ena = 3; 
const int frontR = 12;
const int rearR = 11;
const int enb = 6; 
const int frontL = 7;
const int rearL = 8;

const int echopin = 4;
const int trigpin = 10; 
const int servopin = 9; 

const int frontlimit = 20; 
const int sidelimit = 15; 
Servo head;
int distanceL, distanceF, distanceR;
void speed() {
  analogWrite(ena, 150);
  analogWrite(enb, 150);
}

void turningSpeed() {
  analogWrite(ena, 180);
  analogWrite(enb, 180);
}

void goForward() {
  digitalWrite(frontR, HIGH);
  digitalWrite(rearR, LOW);
  digitalWrite(frontL, HIGH);
  digitalWrite(rearL, LOW);
  speed();
}

void goRight() {
  digitalWrite(frontR, LOW);
  digitalWrite(rearR, HIGH);
  digitalWrite(frontL, HIGH);
  digitalWrite(rearL, LOW);
  turningSpeed();
}

void goLeft()
{
  digitalWrite(frontR, HIGH);
  digitalWrite(rearR, LOW);
  digitalWrite(frontL, LOW);
  digitalWrite(rearL, HIGH);
  turningSpeed();
}

void Stop()
{
  digitalWrite(frontR, LOW);
  digitalWrite(rearR, LOW);
  digitalWrite(frontL, LOW);
  digitalWrite(rearL, LOW);
  analogWrite(ena,0);
  analogWrite(enb,0); 
}
int measureDistance() {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  long duration = pulseIn(echopin, HIGH);
  int distance = duration * 0.034 / 2; 
  return distance;
}

int measure(int angle){
  head.write(angle);
  delay(200);
  return measureDistance();
}
void setup() {
  pinMode(ena, OUTPUT);
  pinMode(frontR, OUTPUT);
  pinMode(rearR, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(frontL, OUTPUT);
  pinMode(rearL, OUTPUT);
  head.attach(servopin);
  head.write(90);
  delay(300);
  goForward();

}

void solvemaze(){
  // three different ways
  distanceL = measure(150);
  distanceF = measure(90);
  distanceR = measure(30);

  
  
if(distanceF < frontlimit ){
  
  if(distanceL > sidelimit){
    goLeft();
  }
  else if(distanceR > sidelimit) {
    goRight(); 
  }
} else{
  goForward();
}
}

void loop() {
  solvemaze(); 

}
