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

const int leftSensor = 5;
const int rightSensor = 2; 
Servo head;
int distanceL, distanceF, distanceR;

void speed() {
  analogWrite(ena, 110);
  analogWrite(enb, 110);
}

void turningSpeedBig() {
  analogWrite(ena, 160);
  analogWrite(enb, 160);
}

void turningSpeedSmall() {
  analogWrite(ena, 130);
  analogWrite(enb, 130);
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
  turningSpeedBig();
}

void goRightSmall() {
  digitalWrite(frontR, LOW);
  digitalWrite(rearR, HIGH);
  digitalWrite(frontL, HIGH);
  digitalWrite(rearL, LOW);
  turningSpeedSmall();
}

void goLeft()
{
  digitalWrite(frontR, HIGH);
  digitalWrite(rearR, LOW);
  digitalWrite(frontL, LOW);
  digitalWrite(rearL, HIGH);
  turningSpeedBig();
}

void goLeftSmall()
{
  digitalWrite(frontR, HIGH);
  digitalWrite(rearR, LOW);
  digitalWrite(frontL, LOW);
  digitalWrite(rearL, HIGH);
  turningSpeedSmall();
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

int measure(){
  head.write(90);
  delay(150);
  return measureDistance();
}
void setup() {
  pinMode(ena, OUTPUT);
  pinMode(frontR, OUTPUT);
  pinMode(rearR, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(frontL, OUTPUT);
  pinMode(rearL, OUTPUT);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  head.attach(servopin);
  delay(300);
  Serial.begin(9600); 
}

void solvemaze() {
    distanceF = measure(); 
    int leftValue = digitalRead(leftSensor);
    int rightValue = digitalRead(rightSensor);
    // detects a wall less than 20 centimeters away
    if (distanceF < frontlimit) {
        Stop();
        delay(100);
        // detects a wall on the left, goes right
        if (leftValue == LOW) {
            goRight();
        } 
        // otherwise goes left
        else {
            goLeft();  
        }
    }
    // detects a wall on the left, goes slighty right
    else if (leftValue == LOW) {
        goRightSmall();
    }
    // detects a wall on the right, goes slighty left 
    else if (rightValue == LOW){
        goLeftSmall();
    }
    // otherwise goes straight 
    else {
        goForward();
    }

    delay(50);
}
void loop() { 
  solvemaze(); }
