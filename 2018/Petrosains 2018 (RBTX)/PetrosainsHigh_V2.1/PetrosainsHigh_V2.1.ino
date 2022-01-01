

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

int IR0 = A0;                                                    //upper
int IR1 = A1;
int IR2 = A2;
int IR3 = A3;
int IR4 = A4;
int IR5 = A5;

/////////////////////////////////////////////////////////////////////////////////////
int LW = 0;//Left Wall
int L = 1;//Left
int S = 2;//Straight
int R = 3;//Right
int RW = 4; //Right Wall
/////////////////////////////////////////////////////////////////////////////////////

int SetPath[] = {
  R,L,S,R,R,R,S

};


/////////////////////////////////////////////////////////////////////////////////////

int timer = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int turnSpeed = 50;
int turnTime = 500;
int moveTime = 1000;

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
  //Calibrate();
  // Left();

  if (((analogRead(IR0)) < 500) && ((analogRead(IR3)) < 500)) {
    if ((analogRead(IR4) < 500) || (analogRead(IR5) < 500)) {
      brake();
      decision();
    }
    else {
      wallFollow();
    }
  }
  else {
    decision();    
       forward(motorLeft, motorRight, 150);
       delay(500);
       brake();
  }
}

void Calibrate() {
  while ((analogRead(IR4) < 500) || (analogRead(IR5) < 500)) {

    if (analogRead(IR4) > 500) {
      motorLeft.brake();
    }
    else if (analogRead(IR4) < 500) {
      motorLeft.drive(-55, 1);
    }

    if (analogRead(IR5) > 500) {
      motorRight.brake();
    }
    else if (analogRead(IR5) < 500) {
      motorRight.drive(-55, 1);
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

void wallFollow() {
  if ((analogRead(IR1) < 500) && (analogRead(IR2) < 500)) { //robot not tuned
    motorLeft.drive(-55, 1);
    motorRight.drive(55, 1);
  }
  else if ((analogRead(IR1) < 500) && (analogRead(IR2) > 500)) { //robot on the left
    motorLeft.drive(100, 1);
    motorRight.drive(0, 1);
  }
  else if ((analogRead(IR1) > 500) && (analogRead(IR2) < 500)) { //robot on the right
    motorLeft.drive(0, 1);
    motorRight.drive(100, 1);
  }
  else if ((analogRead(IR1) > 500) && (analogRead(IR2) > 500)) { //robot in the middle
    motorLeft.drive(100, 1);
    motorRight.drive(100, 1);

  }
}

void wallFollowLeft() {
  if (analogRead(IR1) < 500) { //left see wall
    motorLeft.drive(100, 1);
    motorRight.drive(50, 1);
  }
  else if (analogRead(IR1) > 500) {//left don't see wall
    motorLeft.drive(50, 1);
    motorRight.drive(100, 1);

  }
}
void wallFollowRight() {
  if (analogRead(IR2) < 500) { //right see wall
    motorLeft.drive(50, 1);
    motorRight.drive(100, 1);
  }
  else if (analogRead(IR2) > 500) {//right don't see wall
    motorLeft.drive(100, 1);
    motorRight.drive(50, 1);

  }
}


void LeftWall() {

}

void Left() {
  while ((analogRead(IR4) > 500) && (analogRead(IR5) > 500)) {
    motorLeft.drive(100, 1);
    motorRight.drive(100, 1);
  }
  Calibrate();
   timer = millis();
  while ((millis() - timer) < turnTime) {
    motorLeft.drive(-100, 1);        //turn left for ___second
    motorRight.drive(100, 1);
  }
  while (analogRead(IR2) < 500) {
    motorLeft.drive(-turnSpeed, 1);
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  
   timer = millis();
  while ((analogRead(IR3) > 500)&&((millis() - timer) < moveTime)) {
    wallFollowRight();
  }
  brake();
}

void Straight() {
       forward(motorLeft, motorRight, 150);
       delay(500);
       brake();
}
void Right() {
  while ((analogRead(IR4) > 500) && (analogRead(IR5) > 500)) {
    motorLeft.drive(100, 1);
    motorRight.drive(100, 1);
  }
  Calibrate();
   timer = millis();
  while ((millis() - timer) < turnTime) {
    motorLeft.drive(100, 1);        //turn left for ___second
    motorRight.drive(-100, 1);
  }
  while (analogRead(IR1) < 500) {
    motorLeft.drive(turnSpeed, 1);
    motorRight.drive(-turnSpeed, 1);
  }
  brake();
   timer = millis();
  while ((analogRead(IR3) > 500)&&((millis() - timer) < moveTime)) {
    wallFollowLeft();
  }
  brake();
}
void RightWall() {

}
