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

int IR0 = A0;
int IR1 = A1;//left sensor                                                      //pin
int IR2 = A2;
int IR3 = A3;
int IR4 = A4;
int IR5 = A5;//right sensor


/////////////////////////////////////////////////////////////////////////////////////
//others

int L = 0;//Left
int LS = 1;
int LC = 2;
int S = 3;
int RC = 4;
int RS = 5;
int R = 6;

/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {
  /*R,S,L,
    R,
    L,L,R,L,R,L,L,R,R,L,S,L,R*/




  // R, L, L, R, R, L, L, R, R, L, L, L, R, L, R, L, S, L, R, L, R
  //R, S, LC,RC,L,LS,RS,L,LS,RS,R,RS,L
//LC,RC
RC,RS,RS,RS,L,RS,LS
//L,S,L,S,R,L
};


int turnSpeed = 50;
int Time = 200;
int CurveTime = 100;

int SetSpeed = 150;
int SetDifferent = 50;

int SetCurveSpeed = 100;
int SetCurveDifferent = 100;

/////////////////////////////////////////////////////////////////////////////////////
int different = 100;
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Side = 1;
int Speed = 200;

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

  if ((analogRead(IR1) < 500) && (analogRead(IR5) < 500)) {
    Curve();
    //lineFollow();
  }
  else {
    brake();
    delay(000);
    decision();
  }
}


void Curve() {
  if (Side == 1) {
    if (analogRead(IR2) > 500) {
      different = (Speed+Speed) ;
      turnLeft();
    }
    else {

      if (analogRead(IR3) < 500) {
        turnRight();
      }
      else if (analogRead(IR3) > 500) {
        turnLeft();
      }

    }
  }
  else if (Side == 0) {
    if (analogRead(IR4) > 500) {
      different = (+Speed+Speed) ;
      turnRight();
    }
    else {

      if (analogRead(IR3) < 500) {
        turnLeft();
      }
      else if (analogRead(IR3) > 500) {
        turnRight();
      }

    }
  }

}






void lineFollow() {
  if (Side == 0) {
    if (analogRead(IR3) > 500) {
      turnRight();
    }
    else if (analogRead(IR3) < 500) {
      turnLeft();
    }
  }
  else if (Side == 1) {
    if (analogRead(IR3) > 500) {
      turnLeft();
    }
    else if (analogRead(IR3) < 500) {
      turnRight();
    }
  }

}








void turnLeft() {
  motorLeft.drive((Speed - different), 1);
  motorRight.drive(Speed, 1);
}
void turnRight() {
  motorLeft.drive(Speed, 1);
  motorRight.drive((Speed - different), 1);
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
      //Left
      Left();
    }
    else if (SetPath[Turned] == 1) {
      //Right
      ShortLeft();
    }
    else if (SetPath[Turned] == 2) {
      //Right
      CurveLeft();
    }
    else if (SetPath[Turned] == 3) {
      //Straight
      Straight();
    }
    else if (SetPath[Turned] == 4) {
      //Right
      CurveRight();
    }
    else if (SetPath[Turned] == 5) {
      //Right
      ShortRight();
    }
    else if (SetPath[Turned] == 6) {
      //Right
      Right();
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
void Left() {
  brake();

  brake();
  motorRight.drive(255, Time);

  brake();
  while (analogRead(IR0) > 500) {
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = 0;
  Speed = SetSpeed;
  different = SetDifferent;
}
void ShortLeft() {
  brake();

  brake();
  motorRight.drive(255, Time);

  brake();
  while (analogRead(IR3) > 500) {
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = 0;
  Speed = SetSpeed;
  different = SetDifferent;
}
void CurveLeft() {

  brake();

  brake();
  motorRight.drive(255, CurveTime);

  brake();
  while (analogRead(IR3) < 500) {
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = 0;
  Speed = SetCurveSpeed;

  different = SetCurveDifferent;
}
void Straight() {
  while ((analogRead(IR1) > 500) || (analogRead(IR5) > 500)) {
    lineFollow();
  }
int  timer=millis();
/*while ((millis()-timer)<200) {
    lineFollow();
  }*/

}
void CurveRight() {
  brake();

  brake();
  motorLeft.drive(255, CurveTime);
  brake();
  while (analogRead(IR3) < 500) {
    motorLeft.drive(turnSpeed, 1);
  }
  brake();
  Side = 1;
  Speed = SetCurveSpeed;
  different = SetCurveDifferent;



}
void ShortRight() {
  {
    brake();

    brake();
    motorLeft.drive(255, Time);
    brake();
    while (analogRead(IR3) > 500) {
      motorLeft.drive(turnSpeed, 1);
    }
    brake();
    Side = 1;
    Speed = SetSpeed;

    different = SetDifferent;
  }

}
void Right() {
  {
    brake();

    brake();
    motorLeft.drive(255, Time);
    brake();
    while (analogRead(IR0) > 500) {
      motorLeft.drive(turnSpeed, 1);
    }
    brake();
    Side = 1;
    Speed = SetSpeed;

    different = SetDifferent;
  }
}
