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

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


/////////////////////////////////////////////////////////////////////////////////////

int Button = 4;

int IR1 = A5;//left sensor                                                      //pin
int IR2 = A4;
int IR3 = A3;
int IR4 = A1;
int IR5 = A0;//right sensor


/////////////////////////////////////////////////////////////////////////////////////
                                                           //others

int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {S,L,S,L,
S,L,S,R,S,R,L,L,L
  //S,L,S,L,S,S,L,S,L
 // S,R,S,R,S,S,R,S,R
};
int Side = 0;





/////////////////////////////////////////////////////////////////////////////////////
int Time = 200;
int Speed = 180;
int different = 40;
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int timer=0;
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
  timer=millis();
}

void loop() {
  timer=millis();
  if ((digitalRead(IR1) == 1) && (digitalRead(IR5) == 1)) {
    lineFollow();

    if (different>40){
      different=different-0.5;
      }
  }
  else {
    brake(motorRight, motorLeft);
    decision();
  }
}


/////////////////////////////////////////////////////////////////////////////////////
void lineFollow() {
  if (Side == 0) {
    if (digitalRead(IR3) == 0) {
      turnRight();
    }
    else if (digitalRead(IR3) == 1) {
      turnLeft();
    }
  }
  else if (Side == 1) {
    if (digitalRead(IR3) == 0) {
      turnLeft();
    }
    else if (digitalRead(IR3) == 1) {
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
  while (digitalRead(IR3) == 1) {
    motorRight.drive(100, 1);
  }
  brake(motorRight, motorLeft);
  different=100;
  last=millis();
  Side = 0;
}

void Straight() {
  while((digitalRead(IR1) == 0)||(digitalRead(IR5) == 0)){
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
  while (digitalRead(IR3) == 1) {
    motorLeft.drive(100, 1);
  }
  brake(motorRight, motorLeft);
  different=100;
  last=millis();
  Side = 1;
}
  }























