#include <MPU6050_tockn.h>  //mpu6050
#include <Wire.h>           //ic2  
#include <Ultrasonic.h>     //ultrasonic                              //libraries 
#include <SparkFun_TB6612.h>//motor driver

MPU6050 gyro(Wire);

Ultrasonic ultrasonic(12, 13); //(Trig,Echo)//ultrasonic
int IR1 = 4;                                                          //pin
int IR2 = 3;
//==================================================================//
#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11                                                       //motor

const int offsetA = -1;
const int offsetB = -1;            //motor direction

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

//==================================================================//


int left1 = 10; //timing
int right1 = 15;
int left2 = 20;
int right2 = 25;                                                        //program flow

int change = 5; //how smooth it follow wall


int target = 0;
int absolute = 0;
//==//
void setup() {                                                         //setup
  Wire.begin();
  gyro.begin();
  Serial.begin(9600);
  gyro.calcGyroOffsets(true);
}

//==//
void loop() {                                                          //main program
  gyro.update();

  absolute = gyro.getAngleZ();

  Serial.println(gyro.getAngleZ());
  digitalWrite(6, HIGH);
  Heading(150);
  Straight(200);
  //Solver();

}

//==//
void Heading(int Speed) {                                              //heading
  while (abs(absolute - target ) > 2) {
    gyro.update();
    absolute = gyro.getAngleZ();
    if (gyro.getAngleZ() > target) {
      motorLeft.drive(-Speed, 1);
      motorRight.drive(Speed, 1);
      gyro.update();
      Serial.println(gyro.getAngleZ());
      //turnLeft(255);
    }
    else if (gyro.getAngleZ() < target) {
      motorLeft.drive(Speed, 1);
      motorRight.drive(-Speed, 1);
      gyro.update();
      Serial.println(gyro.getAngleZ());
      //turnRight(255);
    }
    if (Speed > 80) {

      Speed = Speed - 1;
    }
    else {

    }

  }
  Stop();
}

//==//
void Straight(int straightSpeed) {                                                      //go straight
  int rightSpeed = straightSpeed + (absolute - target);
  int leftSpeed = straightSpeed - (absolute - target);

  motorLeft.drive(leftSpeed, 1);
  motorRight.drive(rightSpeed, 1);
}

//==//
void turnLeft(int S) {                                                 //void motor
  motorLeft.drive(-S, 1);
  motorRight.drive(S, 1);
  //left(motor1, motor2, S);
}
void turnRight(int S) {
  motorLeft.drive(S, 1);
  motorRight.drive(-S, 1);
  //right(motor1, motor2, S);
}
void Stop() {
  brake(motorLeft, motorRight);
}
void Move(int S) {
  forward(motorLeft, motorRight, S);
}

//==//
/*void Solver() {                                                       // solver
  while (ultrasonic.distanceRead() <= 23) {
    if (millis < left1) {
      followRight();
    }
    else if ((millis >= left1) && (millis <= right1)) {
      followLeft();
    }
    else if ((millis > right1) && (millis < left2)) {
      followRight();
    }
    else if ((millis >= left2) && (millis <= right2)) {
      followLeft();
    }
    else if (millis > right2) {
      followRight();
    }
  }
*/

//==================================================================//






