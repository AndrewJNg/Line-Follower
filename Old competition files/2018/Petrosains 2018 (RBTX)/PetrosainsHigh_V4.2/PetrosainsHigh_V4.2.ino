
int LW = 0;//Left Wall
int L = 1;//Left
int S = 2;//Straight
int R = 3;//Right
int RW = 4; //Right Wall
int B = 5; //turn 180 degree

/////////////////////////////////////////////////////////////////////////////////////
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

int Button = 4;

int IR0 = A0;
int IR1 = A1;
int IR2 = A2;
int IR3 = A3;
int IR4 = A4;
int IR5 = A5;

/////////////////////////////////////////////////////////////////////////////////////

int SetPath[] = {

  L






};

int LeftWallDistance = 300; // 0-550
int RightWallDistance = 300; // 0-550
int differential = 100;    //100
int Speed = 150;          //150
int StraightTime = 30;     //30
int turnSpeed = 100;       //100
int moveTime = 800;        //800
int turnTimeLeft = 250;    //250
int turnTimeRight = 350;   //250
/////////////////////////////////////////////////////////////////////////////////////

long timer = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;






void setup() {
  pinMode(Button, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  while (digitalRead(Button) == LOW); {
  }
  delay(1000);

}


void loop() {
if (((analogRead(IR0)) < 500) && ((analogRead(IR1)) < 500) && (analogRead(IR4) + analogRead(IR5)) > 600) {
    if ((analogRead(IR2) < 500) && (analogRead(IR3) < 500)) {
      brake();

      Calibrate();
      decision();

    }
    else if ((analogRead(IR2) > 500) || (analogRead(IR3) > 500)) {
      wallFollow();
    }
  }
  else if (((analogRead(IR0)) > 500) || ((analogRead(IR1)) > 500) || (analogRead(IR4) + analogRead(IR5)) < 600) {
    brake();
    timer = millis();
    while ((millis() - timer) < 100) {
      motorLeft.drive(100, 1);
      motorRight.drive(100, 1);
    }
    delay(1000);
    decision();
    brake();
  }

}


void Calibrate() {
  /*while ((analogRead(IR2) > 500) && (analogRead(IR3) > 500)) {

        motorLeft.drive(50, 1);
        motorRight.drive(50, 1);
        }*/
  while ((analogRead(IR2) < 500) || (analogRead(IR3) < 500)) {

    if (analogRead(IR2) > 500) {
      motorLeft.brake();
    }
    else if (analogRead(IR2) < 500) {
      motorLeft.drive(-100, 1);
    }

    if (analogRead(IR3) > 500) {
      motorRight.brake();
    }
    else if (analogRead(IR3) < 500) {
      motorRight.drive(-100, 1);
    }

  }
  brake();
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
      //Left Wall
      LeftWall();
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
      //Right Wall
      RightWall();
    }
    else if (SetPath[Turned] == 5) {
      //Turn 180
      Turn180();
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

void wallFollow() {              //sees both walls
  float KP = 1;
  int LeftValue = analogRead(IR4);
  int RightValue = analogRead(IR5);
  //int  centre = (LeftValue + RightValue)/2;
  int error = RightValue - LeftValue;
  float PDifferential = (abs(error) * KP);
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

void wallFollowLeft() {         //sees left wall
  float KPL = 1;
  int LeftValueL = analogRead(IR4);
  int RightValueL = 300;
  //int  centre = (LeftValue + RightValue)/2;
  int errorL = RightValueL - LeftValueL;
  float PDifferentialL = (abs(errorL) * KPL);
  if (errorL < 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive((Speed - PDifferentialL), 1);
  }
  else if (errorL > 0) {
    motorLeft.drive((Speed - PDifferentialL), 1);
    motorRight.drive(Speed, 1);
  }
  else if (errorL == 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive(Speed, 1);
  }
}
void wallFollowRight() {        //sees right wall
  float KPR = 1;
  int LeftValueR = 300;
  int RightValueR = analogRead(IR5);
  //int  centre = (LeftValue + RightValue)/2;
  int errorR = RightValueR - LeftValueR;
  float PDifferentialR = (abs(errorR) * KPR);
  if (errorR < 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive((Speed - PDifferentialR), 1);
  }
  else if (errorR > 0) {
    motorLeft.drive((Speed - PDifferentialR), 1);
    motorRight.drive(Speed, 1);
  }
  else if (errorR == 0) {
    motorLeft.drive(Speed, 1);
    motorRight.drive(Speed, 1);
  }
}


void LeftWall() {
  while (analogRead(IR5) > 200) {//still on same wall
    wallFollowLeft();
  }
  timer = millis();
  while ((millis() - timer) < 400) {//follow left wall for
    wallFollowLeft();
  }
  int value = (analogRead(IR4) + analogRead(IR5));

  while (value < 500) {
    value = (analogRead(IR4) + analogRead(IR5));
    wallFollowLeft();
  }
}

void Left() {
  
    brake();
    motorRight.drive(100,450);
brake();
}

void Straight() {
  timer = millis();
    while ((millis() - timer) < 440) {
      motorLeft.drive(100, 1);
      motorRight.drive(100, 1);
    }
    brake();
}

void Right() {

  timer = millis();
    while ((millis() - timer) < 100) {
      motorLeft.drive(100, 1);
      motorRight.drive(100, 1);
    }
    brake();
motorLeft.drive(100,450);
brake();

  timer = millis();
    while ((millis() - timer) < 100) {
      motorLeft.drive(100, 1);
      motorRight.drive(100, 1);
    }
    brake();
}

void RightWall() {
  while (analogRead(IR4) > 200) {//still on same wall
    wallFollowRight();
  }
  timer = millis();
  while ((millis() - timer) < 400) {//follow left wall for
    wallFollowRight();
  }
  int value = (analogRead(IR4) + analogRead(IR5));

  while (value < 400) {
    value = (analogRead(IR4) + analogRead(IR5));
    wallFollowRight();
  }
}

void Turn180() {
timer = millis();
    while ((millis() - timer) < 550) {
      motorLeft.drive(-100, 1);
      motorRight.drive(100, 1);
    }










}
