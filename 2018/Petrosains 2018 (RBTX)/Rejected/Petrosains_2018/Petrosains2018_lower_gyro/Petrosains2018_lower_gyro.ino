#include <MPU6050_tockn.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>

MPU6050 gyro(Wire);

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11

const int offsetA = 1;
const int offsetB = 1;

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int IR1 = A7;//left sensor                                                          //pin
int IR2 = A6;
int IR3 = A3;                                                          //pin
int IR4 = A2;
int IR5 = A1;//right sensor
int i = 0;
int NormalSpeed = 160;
int target =0;
int absolute =0;

int L = 0;
int S = 1;
int R = 2;



int turn[] = {L,S,L,S,L,S,S,L,S,L,L
             };
int timetoturn = 310;


int colour = 0;



void setup()
{ Serial.begin(9600);
  Wire.begin();
  gyro.begin();
  gyro.calcGyroOffsets(true);
}


void loop()
{  
  gyro.update();

  absolute = gyro.getAngleZ();
  Serial.print(digitalRead(IR1));
  Serial.print("   ");
  Serial.print(digitalRead(IR2));
  Serial.print("   ");
  Serial.print(digitalRead(IR3));
  Serial.print("   ");
  Serial.print(digitalRead(IR4));
  Serial.print("   ");
  Serial.print(digitalRead(IR5));
  Serial.println("  ");

  if ((digitalRead(IR1) == 1) && (digitalRead(IR5) == 1)) {
    if (digitalRead(IR4) == 0) {
      turnRight(NormalSpeed);    //turn when IR4 see line
    }
    else {
      linefollow();                  //keep following the line with IR3

    }
  }
  else if ((digitalRead(IR1) == 0) && (digitalRead(IR5) == 1)) {
    decision();
  }
  else if ((digitalRead(IR1) == 1) && (digitalRead(IR5) == 0)) {
    decision();
  }
  else {
    decision();
  }
}
void linefollow() {
  if ( (digitalRead(IR3) == 1) && (colour == 0)) {
    turnLeft(NormalSpeed);
  }
  else if ( (digitalRead(IR3) == 0) && (colour == 0)) {
    turnRight(NormalSpeed);
  }
  if ( (digitalRead(IR3) == 1) && (colour == 1)) {
    turnRight(NormalSpeed);
  }
  else if ( (digitalRead(IR3) == 0) && (colour == 1)) {
    turnLeft(NormalSpeed);
  }
}
void turnLeft(int S) {                                                 //void motor
  motorLeft.drive((S - 20), 1);
  motorRight.drive(S, 1);
  //left(motor1, motor2, S);
}
void turnRight(int S) {

  motorLeft.drive(S, 1);
  motorRight.drive((S - 20), 1);
  //right(motor1, motor2, S);
}
void decision() {                                            //decision
  int y = (sizeof(turn)) / 2;
  if (i < y)  {
    Serial.println(y);
      gyro.update();

  absolute = gyro.getAngleZ();

    if (turn[i] == 0) {
      Serial.print("left");

    brake(motorLeft, motorRight);
     target=target-90;
      colour = 0;
    }

    else if (turn[i] == 1) {

      Serial.print("straight");

      forward(motorLeft, motorRight, 255);  //straight
      delay(150);
      brake(motorLeft, motorRight);
    }

    else if (turn[i] == 2) {

    brake(motorLeft, motorRight);
      Serial.print("right");
      target=target+90;
      colour = 1;

    }
  }
  else {
    /*brake(motorLeft, motorRight);
    motorRight.drive(255, (timetoturn + 50)); //left
    brake(motorLeft, motorRight);
    motorLeft.drive(-255, timetoturn);//right
    brake(motorLeft, motorRight);
    delay(100);
    forward(motorLeft, motorRight, 255);  //straight
    delay(200);
    brake(motorLeft, motorRight);
    delay(3000);
    i = -1;*/
      brake(motorLeft, motorRight);
    delay(100000);


  }
  brake(motorLeft, motorRight);
  delay(00);
  i = i + 1;
  
  Heading(150);
}


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
    brake(motorLeft, motorRight);
}
