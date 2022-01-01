#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9                                                  //motor 
#define BIN2 10
#define PWMB 11



/////////////////////////////////////////////////////////////////////////////////////

int Button = 4;

int IR1 = A1;//left sensor                                                      //pin
int IR2 = A2;
int IR3 = A3;
int IR4 = A6;
int IR5 = A7;//right sensor


/////////////////////////////////////////////////////////////////////////////////////


int W = 0;  //White  
int B = 1;  //Black                                                           //others

int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {//L,S,L,S,L,S,L
L,L,R,R,R,R,L,L,L,L,S,L,L,L,S,L,L,S,L
};
int BackGround = W; //(W,B);

int Time = 250;




const int offsetA = 1;
const int offsetB = 1;


/////////////////////////////////////////////////////////////////////////////////////

Motor motorLeft = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorRight = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int Speed = 255;
int different = 20;
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int last=0;
void setup() {
  pinMode(Button, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  while (digitalRead(Button) == LOW); {

  }
  delay(2000);
}



void loop() {
  if ((analogRead(IR1) >500) && (analogRead(IR5) >500)) {
    lineFollow();

    if (different>40){
      different=different-0.3;
      }
  }
  else {
    brake(motorRight, motorLeft);
    decision();
  }
}


/////////////////////////////////////////////////////////////////////////////////////
void lineFollow() {
  if (BackGround == 0) {
    if (analogRead(IR3) <500) {
      turnRight();
    }
    else if (analogRead(IR3) >500) {
      turnLeft();
    }
  }
  else if (BackGround == 1) {
    if (analogRead(IR3) <500) {
      turnLeft();
    }
    else if (analogRead(IR3) >500) {
      turnRight();
    }
  }

}
/////////////////////////////////////////////////////////////////////////////////////
void turnLeft() {
  motorLeft.drive((Speed-different), 1);
  motorRight.drive(Speed, 1);
}
void turnRight() {
  motorLeft.drive(Speed, 1);
  motorRight.drive((Speed-different), 1);
}
/////////////////////////////////////////////////////////////////////////////////////
void decision() {
  if (Turned < TotalTurns) {
    if (SetPath[Turned] == 0) {
      //Left
      Left();
    }
    else if (SetPath[Turned] == 1) {
      //Straight
      Straight();
    }
    else if (SetPath[Turned] == 2) {
      //Right
      Right();
    }
  }

  else {
    //Stop
  brake(motorRight, motorLeft);
  
    while (digitalRead(Button) == HIGH); {

  }
  //delay(2000);
  Straight();
    Turned=-1;
  }

  //
  Turned = Turned + 1;
}

void Left() {
  brake(motorRight, motorLeft);
  
  brake(motorRight, motorLeft);
  motorRight.drive(255, Time);
  //while (digitalRead(IR2) == 1) {
  //  motorRight.drive(255, 1);
  //}
  
  brake(motorRight, motorLeft);
  while (analogRead(IR3) >500) {
    motorRight.drive(100, 1);
  }
  brake(motorRight, motorLeft);
  different=120;
  last=millis();
  BackGround = 0;
}

void Straight() {
  while((analogRead(IR1) <500)||(analogRead(IR5) <500)){
  lineFollow();
  }
}

void Right() {
  {
  brake(motorRight, motorLeft);
  
  brake(motorRight, motorLeft);
  motorLeft.drive(255, Time);
  //while (digitalRead(IR2) == 1) {
  //  motorRight.drive(255, 1);
  //}
  
  brake(motorRight, motorLeft);
  while (analogRead(IR3) >500) {
    motorLeft.drive(100, 1);
  }
  brake(motorRight, motorLeft);
  different=120;
  last=millis();
  BackGround = 1;
}
  }
