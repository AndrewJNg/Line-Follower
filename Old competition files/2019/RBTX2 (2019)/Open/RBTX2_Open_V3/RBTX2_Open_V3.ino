//version 3
#include <EEPROM.h>
#include <HCSR04.h>


#define PWMA 5
#define AI2 6
#define AI1 7
#define STBY 8
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
int IR[] = {  A1, A2, A3, A4, A5, A6, A7, A0};
unsigned int minIR[] = {1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024};
unsigned int midIR[] = {512, 512, 512, 512, 512, 512, 512, 512, 512, 512};
unsigned int maxIR[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int get_state[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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
      //Junction(Left Speed ,Right Speed, kp, kd, type,  action)
     //type    = { L , M , R }
      //action= {{ i , L , R , s }
      Straight(255, 255,1, 100,2 000);
      Junction(200, 200, 1, 100, 'R', 'R');
      Straight(255, 255,1, 100,10 000);
      Junction(200, 200, 1, 100, 'M', 'i');
      Junction(200, 200, 1, 100, 'M', 's');
    }
    else if (Mode == 3) {
      //Path 2
      Junction(190, 190, 1, 100, 'M', 'i');
      Junction(190, 190, 1, 100, 'M', 'i');
      Junction(190, 190, 1, 100, 'M', 's');
    }
    else if (Mode == 4) {
      //Path
      Junction(180, 180, 1, 100, 'M', 'i');
      Junction(180, 180, 1, 100, 'M', 'i');
      Junction(180, 180, 1, 100, 'M', 's');
    }
  }
  else {
    Stop();
  }
}
