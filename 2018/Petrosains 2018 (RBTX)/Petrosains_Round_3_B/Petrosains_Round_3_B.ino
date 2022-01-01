
int L = 0;
int R = 1;

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

int SetPath[] = {R






                };
int LeftRightFollow = R;

int C1 = 3; //R   3
int C2 = 4; //R   5
int C3 = 5; //L   13
int C4 = 1000; //R    19
int C5 = 1000; //L    22
int C6 = 100; //R    22
int C7 = 111; //L   100
int C8 = 120; //R
int C9 = 50; //
int C10 = 53; //
int C11 = 55; //
int C12 = 156; //
int C13 = 157; //










int Time1 = 10000;
int Time2 = 20000;
int Time3 = 30000;
int Time4 = 40000;
int Time5 = 50000;
int Time6 = 60000;
int Time7 = 70000;
int Time8 = 80000;
int Time9 = 90000;
int Time10 = 100000;
int Time11 = 110000;
int Time12 = 120000;
int Time13 = 130000;
int Time14 = 140000;
int Time15 = 150000;
////////////////////////////////////////////////////////////////////////////////////

long timer = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int timePast = 0;
int Counter = 0;
int SeeWallCounterLeft = 0;
int SeeWallCounterRight = 0;
int SeeWallCounter = 0;
int Past=0;


void setup() {
  pinMode(13, OUTPUT);
  pinMode(Button, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  Serial.begin(9600);

  while (digitalRead(Button) == LOW); {
  }
  delay(1000);

  timer = millis();
}


void loop() {


  timePast = (millis() - timer);
  Serial.print("IR4=");
  Serial.print(analogRead(IR4));
  Serial.print("IR4=");
  Serial.print(analogRead(IR5));

  Serial.println();
  
  
    if ((Counter >= 0) && (Counter < C1)) {

      LeftRightFollow = L;
    }
    else if ((Counter >= C1) && (Counter < C2)) {
      LeftRightFollow = R;
    }

    else if ((Counter >= C2) && (Counter < C3)) {
      LeftRightFollow = R;
    }
    else if ((Counter >= C3) && (Counter < C4)) {
      LeftRightFollow = L;
    }
    else if ((Counter >= C4) && (Counter < C5)) {
      LeftRightFollow = R;
    }
    else if ((Counter >= C5) && (Counter < C6)) {
      LeftRightFollow = L;
    }
    else if ((Counter >= C6) && (Counter < C7)) {
      LeftRightFollow = R;
    }
    else if ((Counter >= C7) && (Counter < C8)) {
      LeftRightFollow = L;
    }
    else if ((Counter >= C8) && (Counter < C9)) {
      LeftRightFollow = R;
    }
    else if ((Counter >= C9) && (Counter < C10)) {
      LeftRightFollow = L;
    }
    else if ((Counter >= C10) && (Counter < C11)) {
      LeftRightFollow = R;
    }
    else if ((Counter >= C11) && (Counter < C12)) {
      LeftRightFollow = L;
    }
    else if ((Counter >= C12) && (Counter < C13)) {
      LeftRightFollow = L;
    }








    //ORW();
    if (LeftRightFollow == 0) {
      OLW();
    }
    else if (LeftRightFollow == 1) {
      ORW();
    }
    else if (LeftRightFollow == 2) {
      turnLeft();
      Straight();
      LeftRightFollow = 0;
    }
    else if (LeftRightFollow == 3) {

  if ((analogRead(IR3) < 400) && (analogRead(IR1) > 400)) {

    motorLeft.drive(100, 1);
    motorRight.drive(200, 1);
  }
  else if ((analogRead(IR3) > 400) && (analogRead(IR1) > 400)) {
    motorLeft.drive(200, 1);
    motorRight.drive(100, 1);
  }
  else if ((analogRead(IR3) < 400) && (analogRead(IR1) < 400)) {
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }
  else if ((analogRead(IR3) > 400) && (analogRead(IR1) < 400)) {
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }

    }
    else if (LeftRightFollow == 4) {
      Straight();
      LeftRightFollow = 0;
    }
    else if (LeftRightFollow == 5) {
  while ((millis()-Past)<1500) {
    OLW();       
  }
  ORW();
    }









  if ((SeeWallCounter == 0) && (analogRead(IR4) < 500) && (analogRead(IR5) < 500)) { //see right
    SeeWallCounter = 1;
  }
  else if ((SeeWallCounter == 1) && (analogRead(IR4) > 500) && (analogRead(IR5) > 500)) {// don't see right
    Counter = Counter + 1;
    SeeWallCounter = 0;
    brake();
    //delay(1000);

  }
  else {

  }

  
}

void ORW() {

  if ((analogRead(IR3) < 400) && (analogRead(IR1) > 400)) {

    motorLeft.drive(60, 1);
    motorRight.drive(200, 1);
  }
  else if ((analogRead(IR3) > 400) && (analogRead(IR1) > 400)) {
    motorLeft.drive(200, 1);
    motorRight.drive(60, 1);
  }
  else if ((analogRead(IR3) < 400) && (analogRead(IR1) < 400)) {
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }
  else if ((analogRead(IR3) > 400) && (analogRead(IR1) < 400)) {
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }


}

void OLW() {
  if ((analogRead(IR2) < 400) && (analogRead(IR0) > 500)) {

    motorLeft.drive(200, 1);
    motorRight.drive(55, 1);
  }
  else if ((analogRead(IR2) > 400) && (analogRead(IR0) > 500)) {
    motorLeft.drive(55, 1);
    motorRight.drive(200, 1);
  }
  else if ((analogRead(IR2) < 400) && (analogRead(IR0) < 500)) {
    motorLeft.drive(100, 1);
    motorRight.drive(-100, 1);
  }
  else if ((analogRead(IR2) > 400) && (analogRead(IR0) < 500)) {
    motorLeft.drive(100, 1);
    motorRight.drive(-100, 1);

  }


}
void decision() {


  if (Turned < TotalTurns) {
    if (SetPath[Turned] == 0) {
      LeftRightFollow = 0;
    }
    else if (SetPath[Turned] == 1) {
      LeftRightFollow = 1;
    }
    else if (SetPath[Turned] == 2) {
      LeftRightFollow = 2;
    }
    else if (SetPath[Turned] == 3) {
      LeftRightFollow = 3;
    }
    else if (SetPath[Turned] == 4) {
      LeftRightFollow = 4;
    }
    
    else if (SetPath[Turned] == 5) {
      LeftRightFollow = 5;
      
      Past = millis();
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
void brake() {
  digitalWrite(STBY, HIGH);

  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);
  analogWrite(PWMA, 255);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMB, 255);
}
void turnLeft() {
  timer = millis();
  while ((millis()-timer) < 1000) { //move back against the wall
    motorLeft.drive(-100, 1);
    motorRight.drive(-100, 1);
  }
  timer = millis();
  while ((millis()-timer) < 1000) {//move front
    motorLeft.drive(100, 1);
    motorRight.drive(100, 1);
  }

  timer = millis();
  while ((millis()-timer) < 500) {          //turn left
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }
}
void turnRight() {

}
void Straight() {
  timer = millis();
  while ((millis()-timer) < 1000) {        //move straight
    motorLeft.drive(100, 1);
    motorRight.drive(100, 1);
  }
}

