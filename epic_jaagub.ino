const int ena = 3; 
const int frontR = 12;
const int rearR = 11;
const int enb = 6; 
const int frontL = 7;
const int rearL = 8;

void speed() {
  analogWrite(ena, 100);
  analogWrite(enb, 100);
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

void setup() {
  pinMode(ena, OUTPUT);
  pinMode(frontR, OUTPUT);
  pinMode(rearR, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(frontL, OUTPUT);
  pinMode(rearL, OUTPUT);
}

void loop() {
  
}
