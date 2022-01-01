#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11
const int offsetA = -1;
const int offsetB = -1;//motor direction
Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print(digitalRead(A0));
  Serial.print(" ");
  Serial.print(digitalRead(4));
  Serial.print(" ");
  Serial.print(digitalRead(A2));
  Serial.print(" ");
  Serial.print(digitalRead(3));
  Serial.print(" ");
  Serial.println(digitalRead(3));
  Serial.print(" ");

  if (digitalRead(4) == 0 ) {
    turnRight(150);
  }
  else if (digitalRead(4) == 1 ) {
    turnLeft(150);
  }
 // else if (digitalRead(4) == 0 ) {
   // turnRight(150);
  //}
  //else if (digitalRead(3) == 1 && digitalRead(4) == 1) {
  //Move(150);
  //}
}
void turnRight(int S) {
  motorLeft.drive(255, 1);
  motorRight.drive(0, 1);
}

void turnLeft(int S) {
  motorLeft.drive(230, 1);
  motorRight.drive(255, 1);
}

void Stop() {
  motorLeft.brake();
  motorRight.brake();
}
void Move(int S) {
  forward(motorLeft, motorRight, S);
}
