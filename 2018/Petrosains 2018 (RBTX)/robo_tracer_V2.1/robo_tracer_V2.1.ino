#include <SparkFun_TB6612.h>

#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9                                                  //motor 
#define BIN2 10
#define PWMB 11


const int offsetA = -1;
const int offsetB = 1;

Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


/////////////////////////////////////////////////////////////////////////////////////

int Button = 4;

int IR1 = A5;//left sensor                                                      //pin
int IR2 = A0;
int IR3 = A4;
int IR4 = A6;
int IR5 = A3;//right sensor


/////////////////////////////////////////////////////////////////////////////////////
//others

int L = 0;//Left
int S = 1;//Straight
int R = 2;//Right


/////////////////////////////////////////////////////////////////////////////////////





int SetPath[] = {
  /*R,S,L,
    R,
    L,L,R,L,R,L,L,R,R,L,S,L,R*/




  //L,S,S,R,L,L,R,R,L,R,L
  //R,R,R,S,L





  R,R,R,L

};



int Average = 300;

/////////////////////////////////////////////////////////////////////////////////////
int Time = 250;
int Speed = 150;
int different = 510;
int Turned = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int turnSpeed = 100;
int Side = 1;


int Black1=250;
int Black2=250;
int Black3=250;

int White1=250;
int White2=250;
int White3=250;

int Average1=250;
int Average2=250;
int Average3=250;



void setup() {
  pinMode(Button, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  while (digitalRead(Button) == LOW)
  {
  }
  delay(2000);
}



void loop() {
  digitalWrite(STBY, HIGH);
  different = 100;
  //lineFollow();
  if ((analogRead(IR1) > Average1) && (analogRead(IR5) > Average3)) {
    //Curve();
    lineFollow();
  }
  else {
    
    Stop();
    delay(1000);
    decision();
  }
}








void lineFollow() {
  if (Side == 0) {
    if (analogRead(IR3) > Average2) {
      turnRight();
    }
    else if (analogRead(IR3) < Average2) {
      turnLeft();
    }
  }
  else if (Side == 1) {
    if (analogRead(IR3) > Average2) {
      turnLeft();
    }
    else if (analogRead(IR3) < Average2) {
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


void Stop() {
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
    Stop();

    while (digitalRead(Button) == HIGH); {

    }
    Turned = -1;
  }


  Turned = Turned + 1;
}
void Left() {
  Stop();

  Stop();
  motorRight.drive(255, Time);

  Stop();
  while (analogRead(IR3) > Average2) {
    motorRight.drive(turnSpeed, 1);
  }
  Stop();
  Side = 1;
}

void Straight() {
  while ((analogRead(IR1) > Average1) || (analogRead(IR5) > Average3)) {
    lineFollow();
  }
}

void Right() {
  {
    Stop();

    Stop();
    motorLeft.drive(255, Time);
    Stop();
    while (analogRead(IR3) > Average2) {
      motorLeft.drive(turnSpeed, 1);
    }
    Stop();
    Side = 0;
  }
}
