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

int Button = 4;

int IR0 = A0;//left sensor                                                      //pin
int IR1 = A1;
int IR2 = A2;//right sensor
int IR3 = A3;
int IR4 = A4;
/////////////////////////////////////////////////////////////////////////////////////
//others
int LC = 0;//Left Curve
int L = 1;//Left
int S = 2;//Straight
int R = 3;//Right
int RC = 4;//Right Curve
int LS = 5;//Left Short
int RS = 6;//Right Short


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {//L,R,S,R,S,R,L
  //L,R,S,RS,L,LS,R,R,RS,L,S,S,LS,RS
  //LS

};
int average = 350;
int turnSpeed = 50;
int Time = 200;
int StraightSpeed = 255;







/////////////////////////////////////////////////////////////////////////////////////
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Speed = 100 ;
int Differential = 0;
int Side = 1;//0 left   / 1 right
int Short = 0;




void setup() {
  pinMode(Button, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);

  while (digitalRead(Button) == LOW); {
  }
  delay(1000);
}





void loop() {
 
   // motorLeft.drive(0, 1);
  //  motorRight.drive(200, 1);
  lineFollow();
}

void lineFollow() {
  float KP =1;
  int Value = analogRead(IR1);
  int error = Value-150  ;
  float PDifferential = ((abs(error) /300)*100);
  if (error < 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive((Speed - PDifferential), 1);
  }
  else if (error > 0) {
    motorLeft.drive((Speed - PDifferential), 1);
    motorRight.drive(Speed, 1);
  }
  else if (error == 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive(Speed, 1);
  }



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

void decision() {
  if (Turned < TotalTurns) {
    if (SetPath[Turned] == 0) {
      //Left Curve
      LeftCurve();
    }
    else if (SetPath[Turned] == 1) {
      //Left
      Left();
    }
    else if (SetPath[Turned] == 2) {
      //Straight
      Straight();

    }
    else if (SetPath[Turned] == 3) {
      //Right
      Right();
    }
    else if (SetPath[Turned] == 4) {
      //RightCurve
      RightCurve();
    }
    else if (SetPath[Turned] == 5) {
      //LeftShort
      LeftShort();
    }
    else if (SetPath[Turned] == 6) {
      //RightShort
      RightShort();
    }
  }

  else {
    //Stop
    brake();

    while (digitalRead(Button) == LOW); {

    }
    Turned = -1;
  }

  Turned = Turned + 1;
}
void LeftShort() {
}
void LeftCurve() {

}
void Left() {
}
void Straight() {
}
void Right() {

}
void RightCurve() {

}

void RightShort() {
}













