#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire, 0.1, 0.9);

#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9                                                  //motor 
#define BIN2 10
#define PWMB 11


const int offsetA = 1;
const int offsetB = 1;

Motor motorLeft = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorRight = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


/////////////////////////////////////////////////////////////////////////////////////
int IR1 = A7;                                                    //upper
int IR2 = A6;
int IR3 = A3;
int IR4 = A2;
/////////////////////////////////////////////////////////////////////////////////////
int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right

/////////////////////////////////////////////////////////////////////////////////////

int SetPath[] = {//R,L,S,R,R,L
  R,L,L,
};


/////////////////////////////////////////////////////////////////////////////////////


int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int turnSpeed = 80;
int Speed = 100;
int different = 20;
int angle = 0;
int BT = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

}


void loop() { 
 // Straight(5000);diff
  if (((analogRead(IR1))<500)&&((analogRead(IR3))<500)){
    wallFollow();
    }
    else { 
      Straight(230);    brake();
    decision();  
    brake();
      }
}




void wallFollow() {
  if (analogRead(IR4) > 500) {
    turnLeft();
  }
  else if (analogRead(IR4) < 500) {
    turnRight();
  }
}
void turnLeft() {
  motorLeft.drive((Speed-different), 1);
  motorRight.drive(Speed, 1);
}
void turnRight() {
  motorLeft.drive(Speed, 1);
  motorRight.drive((Speed-different), 1);
}
void brake() {
  digitalWrite(STBY, HIGH);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 255);
}
void Left(int degree) {
  brake();
    mpu6050.update();
  BT = mpu6050.getAngleZ();
  while ((angle - BT) < degree) {
    //Left
    mpu6050.update();
    angle = mpu6050.getAngleZ();
    motorRight.drive(turnSpeed, 1);
    motorLeft.drive(-turnSpeed, 1);
    Serial.print(BT);
    Serial.print("            ");
    Serial.println(angle);
  }
  brake();

}

void Right(int degree) {
  brake();
    mpu6050.update();
  BT = mpu6050.getAngleZ();
  while ((angle - BT) > -degree) {
    //Left
    mpu6050.update();
    angle = mpu6050.getAngleZ();
    motorRight.drive(-turnSpeed, 1);
    motorLeft.drive(turnSpeed, 1);
    Serial.print(BT);
    Serial.print("            ");
    Serial.println(angle);
  }
  brake();

}

void Straight(int StraighTime) {
  brake();
    mpu6050.update();
  BT = mpu6050.getAngleZ();
  int timer = millis();
  int ShowMillis = millis();

  while (( millis()-timer ) < StraighTime) {

    ShowMillis = millis();
    mpu6050.update();
    Serial.print(BT);
    Serial.print("      ");
    Serial.print(angle);
    Serial.println("     ");
    angle = mpu6050.getAngleZ();
    if (angle > BT) {
      //left
      motorRight.drive(80, 1);
      motorLeft.drive(150, 1);
    }
    else if (angle < BT) {
      //right

      motorRight.drive(150, 1);
      motorLeft.drive(80, 1);

    }
    else {
      motorRight.drive(100, 1);
      motorLeft.drive(100, 1);
      }
  }

brake();
}
void decision() {
  if (Turned < TotalTurns) {
    if (SetPath[Turned] == 0) {
      //Left
      Left(80);
      Straight(400);
    }
    else if (SetPath[Turned] == 1) {
      //Straight
      Straight(400);
    }
    else if (SetPath[Turned] == 2) {
      //Right
      Right(80);
      Straight(400);
    }
  }

  else {
    //Stop
    brake();

    delay(100000000000);
    //Straight();
   // Right();
    Turned = -1;
  }


  Turned = Turned + 1;
}
