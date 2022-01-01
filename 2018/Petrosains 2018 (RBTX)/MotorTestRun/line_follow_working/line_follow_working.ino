
#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11
int colour = 1;

const int offsetA = 1;
const int offsetB = 1;

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int IR1 = A7;//left sensor                                                          //pin
int IR2 = A6;
int IR3 = A3;                                                          //pin
int IR4 = A2;
int IR5 = A1;//right sensor

void setup()
{ Serial.begin(9600);
}


void loop()
{
  if (digitalRead(IR4) ==0) {
    brake(motorLeft, motorRight);
    Serial.print(digitalRead(IR1));
    Serial.print("   ");
    Serial.print(digitalRead(IR2));
    Serial.print("   ");
    Serial.print(digitalRead(IR3));
    Serial.print("   ");
    Serial.print(digitalRead(IR4));
    Serial.print("   ");
    Serial.print(digitalRead(IR5));
    Serial.println(" l ");
   // delay(5000);
    motorLeft.drive(255, 500);
  }
  else {
    linefollow();
    Serial.print(digitalRead(IR1));
    Serial.print("   ");
    Serial.print(digitalRead(IR2));
    Serial.print("   ");
    Serial.print(digitalRead(IR3));
    Serial.print("   ");
    Serial.print(digitalRead(IR4));
    Serial.print("   ");
    Serial.print(digitalRead(IR5));
    Serial.println(" h ");

  }
}
void linefollow() {
  if ( (digitalRead(IR3)) ==1) {
    turnLeft(255);
  }
  else if ( (digitalRead(IR3)) ==0) {
    turnRight(255);
  }
}
void turnLeft(int S) {                                                 //void motor
  motorLeft.drive((0), 1);
  motorRight.drive(S, 1);
  //left(motor1, motor2, S);
}
void turnRight(int S) {

  motorLeft.drive(S, 1);
  motorRight.drive((0), 1);
  //right(motor1, motor2, S);
}
