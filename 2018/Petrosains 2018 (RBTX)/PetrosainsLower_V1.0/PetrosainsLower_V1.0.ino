
#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11

int Button=4;

const int offsetA = 1;
const int offsetB = 1;

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int IR1 = A5;//left sensor                                                          //pin
int IR2 = A4;
int IR3 = A3;                                                          //pin
int IR4 = A1;
int IR5 = A0;//right sensor
int i = 0;
int Speed=200;


int L = 0;
int S = 1;
int R = 2;



int turn[] = {L,L,S,R,R,S,R,R,R,S,R,L,L,L,S,L,R,L,L,L};
int timetoturn = 350;


int colour = 0;



void setup()
{ Serial.begin(9600);
pinMode(Button,INPUT);
while(digitalRead(Button)==LOW);{
  
}
delay(2000);
}


void loop()
{
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
    
      linefollow();                  //keep following the line with IR3

    
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
    turnLeft(60);
  }
  else if ( (digitalRead(IR3) == 0) && (colour == 0)) {
    turnRight(80);
  }
  if ( (digitalRead(IR3) == 1) && (colour == 1)) {
    turnRight(50);
  }
  else if ( (digitalRead(IR3) == 0) && (colour == 1)) {
    turnLeft(60);
  }
}
void turnLeft(int different) {                                                 //void motor
  motorLeft.drive((Speed-different), 1);
  motorRight.drive(Speed, 1);
  //left(motor1, motor2, S);
}
void turnRight(int different) {

  motorLeft.drive(Speed, 1);
  motorRight.drive((Speed-different), 1);
  //right(motor1, motor2, S);
}
void decision() {                                            //decision
  int y = (sizeof(turn)) / 2;
  if (i < y)  {
    Serial.println(y);

    if (turn[i] == 0) {
      Serial.print("left");

      brake(motorLeft, motorRight);
      motorRight.drive(255, timetoturn);//left
      
      brake(motorLeft, motorRight);
      colour = 0;
    }

    else if (turn[i] == 1) {

      Serial.print("straight");
      
      brake(motorLeft, motorRight);

      forward(motorLeft, motorRight, 255);  //straight
      delay(200);
      brake(motorLeft, motorRight);
    }

    else if (turn[i] == 2) {

      Serial.print("right");
      brake(motorLeft, motorRight);
      motorLeft.drive(255, timetoturn);//right

      brake(motorLeft, motorRight);
      colour = 1;

    }
  }
  else {
     /*brake(motorLeft, motorRight);
    motorRight.drive(255, (timetoturn - 30)); //left
    brake(motorLeft, motorRight);
    motorLeft.drive(-255, timetoturn);//right
    brake(motorLeft, motorRight);
    delay(100);
    forward(motorLeft, motorRight, 255);  //straight
    delay(200);
    brake(motorLeft, motorRight);
    delay(3000);*/
   brake(motorLeft,motorRight);
    //delay(10000000000);
    
    forward(motorLeft, motorRight, 255);  //straight
    delay(200);
    brake(motorLeft, motorRight);
    i = -1;


  }
   brake(motorLeft,motorRight);
  i = i + 1;
}

