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

void forward(int speedL, int speedR){
  digitalWrite(STBY, HIGH);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  analogWrite(PWMA, speedL);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMB, speedR);

}
void reverse(int speedL, int speedR){
  digitalWrite(STBY, HIGH);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, speedL);

  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, speedR);
}

void turn_left(int speedL, int speedR, int how_long){
  motorRight.drive(255, how_long);

  Stop();
  while (analogRead(IR[2]) < 500) {
    motorRight.drive(speedR, 1);
  }
  Stop();
}

void turn_right(int speedL, int speedR, int how_long){
  

    Stop();

    Stop();
    motorLeft.drive(255, how_long);
    Stop();
    while (analogRead(IR[2]) < 500) {
      motorLeft.drive(speedL, 1);
    }
    Stop();
}

void Stop(){

  digitalWrite(STBY, HIGH);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 255);
}

