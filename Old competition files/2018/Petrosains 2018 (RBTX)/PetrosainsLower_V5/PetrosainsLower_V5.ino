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
int IR5 = A5;//left sensor                                                      //pin
int IR6 = A6;
int IR7 = A7;//right sensor
/////////////////////////////////////////////////////////////////////////////////////
//others
int LS = 0;//Left Short
int LC = 1;//Left Curve
int L = 2;//Left
int S = 3;//Straight
int R = 4;//Right
int RC = 5;//Right Curve
int RS = 6;//Right Short


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {//RS, L, R, R, RS, LS,RS,LS,LS,RS,L,L,L,R,RS,L,LS
  //S, LS, LS, RS, RS, LS, R, R, LS
S,LS,R,LS,R

};
int average = 350;
int turnSpeed = 100;
int Timer = 200;
int StraightSpeed = 255;







/////////////////////////////////////////////////////////////////////////////////////
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Speed = 200 ;
int Differential = 0;
int Side = 1;//0 left   / 1 right
int Short = 0;
int timer=0;



void setup() {
  pinMode(Button, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR7, INPUT);
  while (digitalRead(Button) == LOW); {
  }
  delay(1000);
}





void loop() {

  // motorLeft.drive(0, 1);
  //  motorRight.drive(200, 1);
  //lineFollow();
  if (Short == 0) {
    if ((analogRead(IR0) > 500) && (analogRead(IR2) > 500)) {
      lineFollow();
    }
    else if ((analogRead(IR0) < 500) || (analogRead(IR2) < 500)) {
      brake();
      //delay(1000);
      decision();
    }
  }
  else if (Short == 1) {
    if ((analogRead(IR3) < 500) && (analogRead(IR7) < 500)) {
      lineFollow();
    }
    else if ((analogRead(IR3) > 500) || (analogRead(IR7) > 500)) {
      brake();
      //delay(1000);
      decision();
    }
  }

}

void lineFollow() {
  if (Side == 1) {



    if (analogRead(IR5) > 500) {

      motorLeft.drive(150, 1);
      motorRight.drive(100, 1);
    }
    else if (analogRead(IR5) < 500) {

      motorLeft.drive(100, 1);
      motorRight.drive(150, 1);
    }


  }
  else if (Side == 0) {



    if (analogRead(IR5) > 500) {

      motorLeft.drive(100, 1);
      motorRight.drive(150, 1);
    }
    else if (analogRead(IR5) < 500) {

      motorLeft.drive(150, 1);
      motorRight.drive(100, 1);
    }


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
      //LeftShort
      LeftShort();
    }
    else if (SetPath[Turned] == 1) {
      //Left Curve
      LeftCurve();
    }
    else if (SetPath[Turned] == 2) {
      //Left
      Left();

    }
    else if (SetPath[Turned] == 3) {
      //Straight
      Straight();
    }
    else if (SetPath[Turned] == 4) {
      //Right
      Right();
    }
    else if (SetPath[Turned] == 5) {
      //RightCurve
      RightCurve();
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
  brake();

  brake();
  timer = millis();
    while ((millis() - timer) < Timer) {
    //motorLeft.drive(-255, 1);
    motorRight.drive(255, 1);
    }

  brake();
  while (analogRead(IR5) < 500) {
    //motorLeft.drive(-turnSpeed, 1);
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = 0;
  Short = 1;
}
void LeftCurve() {

}
void Left() {
  brake();

  brake();
  timer = millis();
    while ((millis() - timer) < Timer) {
    //motorLeft.drive(-255, 1);
    motorRight.drive(255, 1);
    }

  brake();
  while (analogRead(IR5) < 500) {
    //motorLeft.drive(-turnSpeed, 1);
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = 0;
  Short = 0;
}
void Straight() {
  while (analogRead(IR0) < 500 || analogRead(IR2) < 500||analogRead(IR3) > 500||analogRead(IR7) > 500) {
    lineFollow();
  }

}
void Right() {
  brake();

  brake();
  timer = millis();
    while ((millis() - timer) < Timer) {
    motorLeft.drive(255, 1);
   // motorRight.drive(-255, 1);
    }

  brake();
  while (analogRead(IR5) < 500) {
    motorLeft.drive(turnSpeed, 1);
    //motorRight.drive(-turnSpeed, 1);
  }
  brake();
  Side = 0;
  Short = 0;

}
void RightCurve() {
}

void RightShort() {
  brake();

  brake();
  timer = millis();
    while ((millis() - timer) < Timer) {
    motorLeft.drive(255, 1);
    //motorRight.drive(-255, 1);
    }

  brake();
  while (analogRead(IR5) < 500) {
    motorLeft.drive(turnSpeed, 1);
   // motorRight.drive(-turnSpeed, 1);
  }
  brake();
  Side = 0;
  Short = 1;
}













