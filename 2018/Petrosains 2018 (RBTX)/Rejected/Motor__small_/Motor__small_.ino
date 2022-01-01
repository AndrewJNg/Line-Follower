#include <SparkFun_TB6612.h>
int AIN1 = 8;
int BIN1 = 11;
int AIN2 = 9;
int BIN2 = 12;
int PWMA = 3;
int PWMB = 5;
int STBY = 10;
const int offsetA = 1;
const int offsetB = 1;

Motor motorLeft = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorRight = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:
  motorLeft.drive(255, 1);
  motorRight.drive(255,1);
}
