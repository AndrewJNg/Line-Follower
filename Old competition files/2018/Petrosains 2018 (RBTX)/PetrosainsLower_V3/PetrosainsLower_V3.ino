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

int IR1 = A0;//left sensor                                                      //pin
int IR2 = A1;
int IR3 = A2;//right sensor


/////////////////////////////////////////////////////////////////////////////////////
//others

int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {


  
};


int PT = 25;


/////////////////////////////////////////////////////////////////////////////////////
int Time = 250;
int Speed = 200;
int different = 50;
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int turnSpeed = 100;
int Side = 1;
int average = 0;
int value = 0;
int White = 40;
int Black = 800;
int WhiteLine = 100;



void setup() {
  pinMode(Button, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  while (digitalRead(Button) == LOW); {
  }
  //White = analogRead(IR2);
 // Black = analogRead(IR3);
  average = (White + Black) / 2;
  delay(2000);
}


void loop() {
  different=100;
  if ((analogRead(IR1) < WhiteLine) && (analogRead(IR3) < WhiteLine)) {
    lineFollow();
  }
  else {
    brake();
    decision();
  }
}



void lineFollow() {
  value = analogRead(IR2);

  different = (((value - average) * PT) * Side);
  if (different < 0) {
    turnLeft();
  }
  else if (different > 0) {
    turnRight();
  }
  else if (different ==0) {
    motorLeft.drive((Speed), 1);
    motorRight.drive(Speed, 1);
  }
}
















void turnLeft() {
  motorLeft.drive((Speed - abs(different)), 1);
  motorRight.drive(Speed, 1);
}
void turnRight() {
  motorLeft.drive(Speed, 1);
  motorRight.drive((Speed - abs(different)), 1);
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
  while (analogRead(IR2) < WhiteLine) {
    motorRight.drive(turnSpeed, 1);
  }
  brake();
  Side = -1;
}

void Straight() {
  while ((analogRead(IR1) > WhiteLine) || (analogRead(IR3) > WhiteLine)) {
    lineFollow();
  }
}

void Right() {
  {
    brake();

    brake();
    motorLeft.drive(255, Time);
    brake();
    while (analogRead(IR2) < WhiteLine) {
      motorLeft.drive(turnSpeed, 1);
    }
    brake();
    Side = 1;
  }
}
