#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
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
int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right
int B =3;

int SetPath[] = {L

};

int StraightTime=200;
int BT = 0; //before turn
int timer=200;
int Turned=0;
int TotalTurns = ((sizeof(SetPath)) / 2);





void setup() {

  Serial.begin(9600);
  
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets();
}

void loop() {
Left(90);
  Serial.println(mpu6050.getAngleZ());
  
}


void Left(int angle) {
  mpu6050.update();  
  BT = mpu6050.getAngleZ();
  while (BT < angle) {
    
  mpu6050.update();
  angle = mpu6050.getAngleZ();
    motorRight.drive(100, 1);
    motorLeft.drive(-100, 1);
    timer = millis;
  }

  //while (timer < StraightTime) {

    //motorRight.drive(255, 1);
    //motorLeft.drive(255, 1);
  //}
 brake();
  delay(10000);
}

void Straight() {
  // while
  // motorRight.drive(-255, 1);
  //motorLeft.drive(255, 1);
}

void Right(int angle) {
  mpu6050.update();  
  BT = mpu6050.getAngleZ();
  while (BT < angle) {
    motorRight.drive(-255, 1);
    motorLeft.drive(255, 1);
  }



}

void decision() {
  if (Turned < TotalTurns) {
    if (SetPath[Turned] == 0) {
      //Left
      Left(90);
    }
    else if (SetPath[Turned] == 1) {
      //Straight
      Straight();
    }
    else if (SetPath[Turned] == 2) {
      //Right
      Right(90);
    }

    else if (SetPath[Turned] == 3) {
      //Right
      Right(180);
    }
  }

  else {
    //Stop
    brake();

   // while (digitalRead(Button) == HIGH); {

   // }
    //delay(100000000000);
    
   // Right();
    Turned = -1;
  }


  Turned = Turned + 1;
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
