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
//const int sidelimit = 5; 


const int leftSensor = 5;
const int rightSensor = 2; 
Servo head;
int distanceL, distanceF, distanceR;
void speed() {
  analogWrite(ena, 100);
  analogWrite(enb, 100);
}

void turningSpeed() {
  analogWrite(ena, 140);
  analogWrite(enb, 140);
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
void goBackward() {
  // Oikea moottori taaksepäin
  digitalWrite(frontR, LOW);
  digitalWrite(rearR, HIGH);

  // Vasen moottori taaksepäin
  digitalWrite(frontL, LOW);
  digitalWrite(rearL, HIGH);

  // Käytetään normaalia nopeutta taaksepäin
  speed();
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
    Serial.print("Front distance: ");
    Serial.print(distanceF);
    Serial.print(" cm | Left sensor: ");
    Serial.println(leftValue);

    
    if (distanceF < frontlimit) {
        Stop();
        delay(100);
        if (leftValue == LOW) { // näkee esteen
            goRight(); 
        } else if (leftValue == LOW && rightValue == LOW){
          goBackward(); 
          delay(200);
        }
        else {
            goLeft();  
        }
    }
    
    else if (leftValue == LOW) {
        goRight();
    }
    else if (rightValue == LOW){
        goLeft();
    }
    else {
        goForward();
    }

    delay(50);
}
void loop() { solvemaze(); }
