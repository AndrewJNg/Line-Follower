
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

int Time1=10000;
int Time2=20000;
int Time3=30000;
int Time4=40000;
int Time5=50000;
int Time6=60000;
int Time7=70000;
int Time8=80000;
int Time9=90000;
int Time10=100000;
int Time11=110000;
int Time12=120000;
int Time13=130000;
int Time14=140000;
int Time15=150000;
////////////////////////////////////////////////////////////////////////////////////
int LeftWallDistance = 300; // 0-550
int RightWallDistance = 300; // 0-550
int differential = 200;    //100
int Speed = 200;          //150
int StraightTime = 30;     //30
int turnSpeed = 100;       //100
int moveTime = 800;        //800
int turnTimeLeft = 250;    //250
int turnTimeRight = 350;   //250x

long timer = 0;
int TotalTurns = ((sizeof(SetPath)) / 2);
int Turned = 0;
int timePast = 0;





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

  timer = millis();
}


void loop() {
  timePast = (millis()-timer);
  OLW();
  /*if ((timePast >=0) && (timePast <Time1)) {
    ORW();
  }
else  if ((timePast >=Time1 )&& (timePast <Time2)) {
    ORW();
  }
else  if ((timePast >=Time2 )&& (timePast <Time3)) {
    OLW();
  }
else  if ((timePast >=Time3) && (timePast <Time4)) {
    ORW();
  }
else  if ((timePast >=Time4) && (timePast <Time5)) {
    OLW();
  }
else  if ((timePast >=Time5) && (timePast <Time6)) {
    ORW();
  }
else  if ((timePast >=Time6) && (timePast <Time7)) {
    OLW();
  }
else  if ((timePast >=Time7) && (timePast <Time8)) {
    ORW();
  }
else  if ((timePast >=Time8) && (timePast <Time9)) {
    OLW();
  }
else  if ((timePast >=Time9) && (timePast <Time10)) {
    ORW();
  }
else  if ((timePast >=Time10) && (timePast <Time11)) {
    OLW();
  }
else  if ((timePast >=Time11) && (timePast <Time12)) {
    ORW();
  }
else  if ((timePast >=Time12) && (timePast <Time13)) {
    OLW();
  }*/
  
  
  //OnlyLeftWall();
}














    void ORW(){
    //can sense right wall but not front wall
    //then, turn left
    if((analogRead(IR3)<400)&&(analogRead(IR1)>500)){
      motorLeft.drive(70, 1);
      motorRight.drive(255, 1);
  }

  
  //cannot sense right wall and front wall
  //then, turn right
  else if((analogRead(IR3)>400)&&(analogRead(IR1)>500)){
    motorLeft.drive(255, 1);
    motorRight.drive(70, 1); 
  }
  
  //cannot sense right wall, but can sense front wall
  //then turn left by spinning 
  else if((analogRead(IR3)>400)&&(analogRead(IR1)<500)){
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);
  }
  
  //can sense right wall, and can sense front wall
  //then turn left by spinning
  else if((analogRead(IR3)<400)&&(analogRead(IR1)<500)){
    motorLeft.drive(-100, 1);
    motorRight.drive(100, 1);

  }
  



}

void OLW(){  
  //can sense left wall but not front wall
  //then, turn right
  if((analogRead(IR2)<400)&&(analogRead(IR0)>500)){
    motorLeft.drive(255, 1);
    motorRight.drive(70, 1);
  }

  //cannot sense left wall and front wall
  //then, turn left
  else if((analogRead(IR2)>400)&&(analogRead(IR0)>500)){
    motorLeft.drive(60, 1);
    motorRight.drive(255, 1); 
  }

  //cannot sense left wall, but can sense front wall
  //then turn right by spinning 
  else if((analogRead(IR2)>400)&&(analogRead(IR0)<500)){
    motorLeft.drive(100, 1);
    motorRight.drive(-255, 1);
  }
  
  //can sense left wall, and can sense front wall
  //then turn right by spinning
  else if((analogRead(IR2)<400)&&(analogRead(IR0)<500)){
    motorLeft.drive(100, 1);
    motorRight.drive(-255, 1);

  }

}


