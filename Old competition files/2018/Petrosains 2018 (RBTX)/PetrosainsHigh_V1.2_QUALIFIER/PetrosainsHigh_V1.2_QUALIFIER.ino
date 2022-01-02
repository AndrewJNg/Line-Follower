

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

int SetPath[] = {R,L,S,R,R,L
};


/////////////////////////////////////////////////////////////////////////////////////


int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int turnSpeed = 80;
int Speed = 130;
int different = 50;
int angle = 0;
int BT = 0;
int TurnTime=270;

void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

}


void loop() { 
if (((analogRead(IR1))<500)&&((analogRead(IR2))<500)){//turn 180
  
  motorLeft.drive(100, 1);
  motorRight.drive(-100, 1);
  }
  else if (((analogRead(IR1))<500)&&((analogRead(IR2))>500)){
  
  motorLeft.drive(100, 1);
  motorRight.drive(0, 1);
  }
else if (((analogRead(IR1))>500)&&((analogRead(IR2))>500)){
  
  motorLeft.drive(0, 1);
  motorRight.drive(100, 1);
  }
  else if (((analogRead(IR1))>500)&&((analogRead(IR2))>500)){
  
  motorLeft.drive(100, 1);
  motorRight.drive(-100, 1);
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


