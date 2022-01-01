
#include <EEPROM.h>
#include <HCSR04.h>


#define PWMA 5
#define AI2 6
#define AI1 7
#define STBY 0
#define BI1 9
#define BI2 10
#define PWMB 11
#define Echo 8
#define Trig 4

UltraSonicDistanceSensor distanceSensor(Trig, Echo);

//////////////////////////////////////////////////////////////////////////////////////////
#define bStart 2
#define bMode 3
#define buzzer 12
#define led 13

//////////////////////////////////////////////////////////////////////////////////////////

//int LDR = A7;
int IR[] = { A0, A1, A2, A3, A4, A7};
int IRS[] = {A5, A6};
unsigned int minIR[] = {1024, 1024, 1024, 1024, 1024, 1024};
unsigned int midIR[] = {512, 512, 512, 512, 512, 512};
unsigned int maxIR[] = {0, 0, 0, 0, 0, 0};
unsigned int get_state[] = {0, 0, 0, 0, 0,0};

//Mode 1       calibration Mode
//Mode 2       speed 1
//Mode 3       speed 2
//Mode 4       speed 3


//////////////////////////////////////////////////////////////////////////////////////////

//unsigned long currentMillis = 0;
unsigned int Mode = 2;
boolean Start = false;

//////////////////////////////////////////////////////////////////////////////////////////
boolean rightTurn = 0;
boolean leftTurn = 0;

boolean whiteLine = false;

void loop() {
  LDRF();
  IRSF();
  Buzzer();
  Button();

  if (Start) {
    if (Mode == 1) {
      //calibration
      calibration();
    }
    else if (Mode == 2) {
      //Path 1
      //Junction(LSpeed, RSpeed, P, D, juction, action);
      Junction(255,255, 0.2, 20, 'M', 'c');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Buzz(1, 200);
      //C1
      Junction(200, 200, 0.5, 100, 'R', 'R');
      Buzz(1, 200);
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Buzz(1, 200);
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Buzz(1, 200);
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Buzz(1, 200);
      //C2
      Junction(200, 200, 0.4, 10, 'L', 'L');
      Buzz(1, 200);
      Junction(200, 200, 0.5, 30, 'L', 'l');
      Buzz(1, 200);
      Junction(200, 200, 0.4, 10, 'U', 'u');
      Buzz(1, 200);
      Junction(200, 200, 0.4, 5, 'M', 's');
      
      
    }
    else if (Mode == 3) {
      //Path 2
      
    }
    else if (Mode == 4) {
      //Path 3
    //Junction(LSpeed, RSpeed, P, D, juction, action);
      Junction(255,255, 0.2, 20, 'M', 'c');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Buzz(1, 200);
      //C1
      Junction(200, 200, 0.5, 100, 'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20, 'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20, 'R', 'R');
      Buzz(1, 200);
      Junction(150, 150, 0.5, 20, 'U', 'u');
      Buzz(1, 200);
      //C2
      Junction(255, 255, 0.4, 10, 'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 30, 'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.4, 5, 'M', 's');
    }
  }
  else {
    Stop();
  }
}
