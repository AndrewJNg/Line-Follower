#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire,0.1,0.9);


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

int SetPath[] = {
};


/////////////////////////////////////////////////////////////////////////////////////


int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int turnSpeed = 80;
int Speed = 150;
int different = 30;
int angle=0;
int BT=0;

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
  mpu6050.update();
   
  Serial.print("\tangleZ : ");
  Serial.println(angle);


  BT=mpu6050.getAngleZ();
  while ((angle-BT)<90){
    //Left
  mpu6050.update();
   angle=mpu6050.getAngleZ();
    motorRight.drive(100, 1);
    motorLeft.drive(-100, 1);
  Serial.print(BT);
  Serial.print("            ");
  Serial.println(angle);
    }
    brake();
  delay(10000000000);
  }




























  
void wallFollow() {
    if (analogRead(IR4) >500) {
      turnLeft();
    }
    else if (analogRead(IR4) <500) {
      turnRight();
    }
}
void turnLeft() {
  motorLeft.drive(60, 1);
  motorRight.drive(Speed, 1);
}
void turnRight() {
  motorLeft.drive(Speed, 1);
  motorRight.drive(60, 1);
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




