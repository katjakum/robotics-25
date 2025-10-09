#include <AFMotor.h>

// motors
AF_DCMotor frontR(12)
AF_DCMotor rearR(11)
AF_DCMotor frontL(7)
AF_DCMotor rearL(8)

// pins
/*const int SERVO_PIN 9
const int ECHO_PIN 
const int TRIG_PIN
const int BUZZ_PIN*/

// movement
const int forwardSpeed = 80;
const int turningSpeed = 60;
const int turnDelay = 25;
const int uTurnDelay = 50;

void setup() {
  
  moveForward();

}

void loop() {
  
  void moveForward() {
    frontR.setSpeed(forwardSpeed);
    frontL.setSpeed(forwardSpeed);
    frontR.run(FORWARD);
    frontL.run(FORWARD);
  }

}
