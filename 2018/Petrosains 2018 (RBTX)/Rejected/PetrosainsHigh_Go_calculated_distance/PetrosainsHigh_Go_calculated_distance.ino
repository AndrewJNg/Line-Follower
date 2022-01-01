
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
  
Straight();
delay(100);
Straight();
delay(100);
Left();
delay(100);
Straight();
delay(100);
Left();
delay(100);
Straight();
delay(100);
Turn180();
delay(100);
Straight();
delay(100);
Left();
delay(100);
Straight();

while (digitalRead(Button) == LOW); {
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






void LeftWall() {
  
}

void Left() {
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
motorLeft.drive(100,450);
brake();
}

void RightWall() {
  
}

void Turn180() {
timer = millis();
    while ((millis() - timer) < 550) {
      motorLeft.drive(-100, 1);
      motorRight.drive(100, 1);
    }
brake();









}
