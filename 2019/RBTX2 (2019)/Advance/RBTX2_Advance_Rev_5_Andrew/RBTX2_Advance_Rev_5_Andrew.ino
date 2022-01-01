//version 3
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
int IR[] = { A0, A1, A2, A3, A4, A5, A6, A7};
unsigned int minIR[] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
unsigned int midIR[] = {512, 512, 512, 512, 512, 512, 512, 512};
unsigned int maxIR[] = {0, 0, 0, 0, 0, 0, 0, 0};
unsigned int get_state[] = {0, 0, 0, 0, 0, 0, 0, 0};

//Mode 1       calibration Mode
//Mode 2       speed 1
//Mode 3       speed 2
//Mode 4       speed 3


//////////////////////////////////////////////////////////////////////////////////////////

//unsigned long currentMillis = 0;
unsigned int Mode = 4;
boolean Start = false;

//////////////////////////////////////////////////////////////////////////////////////////
boolean rightTurn = 0;
boolean leftTurn = 0;

boolean whiteLine = false;
int minSpeed = 170;
void loop() {
  LDRF();
//  IRSF();
  Buzzer();
  Button();

  if (Start) {
    if (Mode == 1) {
      //calibration
      calibration();
    }
    else if (Mode == 2) {
      //Path 1
      Junction(255, 255, 0.5, 100, 'M', 's');
    }
    else if (Mode == 3) {
      //Path 2
    }
    else if (Mode == 4) {
      //Path 3
      Junction(150, 150, 0.5, 100, 'R', 'i');
      Buzz(2, 100);
      Junction(150, 150, 0.5, 100, 'U', 'A');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'L', 'B');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'R', 'i');
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Buzz(1, 100);
      //      C1
      Junction(150, 150, 0.5, 100, 'L', 'i');
      Junction(255, 255, 0.8, 100, 'L', 'i');
      Junction(255, 255, 0.8, 100, 'R', 'i');
      Junction(255, 255, 0.8, 100, 'L', 'i');
      Junction(255, 255, 0.8, 100, 'R', 'i');
      Junction(150, 150, 0.8, 100, 'M', 'c');
      Buzz(2, 100);
      //      C2
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(255, 255, 0.5, 100, 'R', 'i');
      Junction(255, 255, 0.5, 100, 'R', 'i');
      Junction(255, 255, 0.5, 100, 'M', 'c');
      Buzz(3, 100);
      //      C3

      Junction(150, 150, 0.5, 100, 'R', 'i');
      Junction(150, 150, 0.8, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Junction(150, 150, 0.5, 100, 'L', 'L');
      Junction(150, 150, 0.5, 100, 'R', 'R');
      Buzz(4, 100);
      //      C4
      Junction(255, 255, 0.5, 100, 'M', 'c');
      Junction(255, 255, 0.8, 100, 'M', 'c');
      Junction(200, 200, 0.5, 100, 'R', 'R');
      Junction(200, 200, 0.5, 100, 'L', 'L');
      
      Junction(255, 255, 0.5, 100, 'M', 's');
      
      Buzz(2, 50);
      //      C5
//      Start = 0;
//      Buzz(2, 50);
    }
  }
  else {
    Stop();
  }
}
