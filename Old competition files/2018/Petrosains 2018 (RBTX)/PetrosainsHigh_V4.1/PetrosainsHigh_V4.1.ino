
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

int SetPath[] = { //B
  //RW, LW, LW
  RW, LW, LW, B, RW, RW, LW, B
  //RW,LW,S,B,RW,B,LW,B,RW,B,RW,RW,LW,B
  //RW,LW,LW,B,RW,RW,LW,B,
  //R,L,LW,B,RW,R,L,B
  //RW,LW,RW,L,L,S,L,RW,B,RW,RW,LW,B
  //RW,LW,LW,B,LW,R,R,R,LW,RW,LW
  //RW, LW, RW, B, LW, RW, LW, B
  //RW,LW,S,R,R,R,LW,RW,LW,B

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

  if (((analogRead(IR0)) < 500) && ((analogRead(IR1)) < 500)) {
    if ((analogRead(IR2) < 500) && (analogRead(IR3) < 500)) {
      brake();
      //   delay(1000);
      /*while ((analogRead(IR2) > 500) && (analogRead(IR3) > 500)) {

        motorLeft.drive(50, 1);
        motorRight.drive(50, 1);
        }*/
      Calibrate();
      decision();

    }
    else if ((analogRead(IR2) > 500) || (analogRead(IR3) > 500)) {
      wallFollow();
    }
  }
  else if (((analogRead(IR0)) > 500) || ((analogRead(IR1)) > 500)) {
    brake();
    //delay(1000);
    decision();
    brake();
  }
}


void Calibrate() {
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
    while (digitalRead(Button) == HIGH); {

    }
    Turned = -1;
  }


  Turned = Turned + 1;
}

void wallFollow() {              //sees both walls
  int KP = 1;
  int LeftValue = analogRead(IR4);
  int RightValue = analogRead(IR5);
  //int  centre = (LeftValue + RightValue)/2;
  int error = RightValue - LeftValue;
  int PDifferential = (abs(error) * KP);
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
  int KP = 1;
  int LeftValue = analogRead(IR4);
  int RightValue = 300;
  //int  centre = (LeftValue + RightValue)/2;
  int error = RightValue - LeftValue;
  int PDifferential = (abs(error) * KP);
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
void wallFollowRight() {        //sees right wall
  int KP = 1;
  int LeftValue = 300;
  int RightValue = analogRead(IR5);
  //int  centre = (LeftValue + RightValue)/2;
  int error = RightValue - LeftValue;
  int PDifferential = (abs(error) * KP);
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


void LeftWall() {
  while (analogRead(IR5) < 250) {
    wallFollowLeft();
  }
  brake();
  timer = millis();
  while ((millis() - timer) < 200) {
    wallFollowLeft();
  }
  brake();
  timer = millis();
  while ((analogRead(IR5) < 300) && ((millis() - timer) < 400)) {
    wallFollowLeft();
  }
  brake();
}

void Left() {
}

void Straight() {
}

void Right() {
}

void RightWall() {
  while (analogRead(IR4)  < 250) {
    wallFollowRight();

  }
  timer = millis();
  while ((millis() - timer) < 400) {
    wallFollowRight();
  }
  timer = millis();
  while ((analogRead(IR4) < 250) && ((millis() - timer) < 500)) {
    wallFollowRight();
  }
  brake();
}

void Turn180() {
  int LeftValue = analogRead(IR4);
  int RightValue = analogRead(IR5);

  if (RightValue < LeftValue) {
    timer = millis();
    while ((millis() - timer) < 300) {
      motorLeft.drive(100, 1);
      motorRight.drive(-150, 1);
    }
  }
  else if (RightValue == LeftValue) {
    timer = millis();
    while ((millis() - timer) < 300) {
      motorLeft.drive(100, 1);
      motorRight.drive(-150, 1);
    }
  }
  else if (RightValue > LeftValue) {
    timer = millis();
    while ((millis() - timer) < 500) {
      motorLeft.drive(-150, 1);
      motorRight.drive(100, 1);
    }
  }











}
