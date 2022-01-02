//version 2.7
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
unsigned int Mode = 2;
boolean Start = false;

//////////////////////////////////////////////////////////////////////////////////////////
boolean rightTurn = 0;
boolean leftTurn = 0;

boolean whiteLine = false;
void loop() {
  LDRF();
  //IRSF();
  Buzzer();
  Button();

  if (Start) {
    if (Mode == 1) {
      //calibration
      calibration();
    }
    else if (Mode == 2) {
      //track 1 (Advance)
      //Path 1

      Junction(200, 200, 0.2, 20, 'M', 'c');
      Junction(200, 200, 0.2, 20, 'M', 'c');
      Junction(150, 150, 0.2, 20, 'U', 'A');
      Junction(200, 200, 0.2, 20, 'R', 'R');
      Junction(200, 200, 0.2, 30, 'R', 'R');

      Junction(150, 150, 0.5, 20, 'M', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'r');
      Junction(255, 255, 0.05, 10, 'M', 's');
    }
    else if (Mode == 3) {
      //track 2 (Advance)
      //Path 2

      Junction(200, 200, 0.2, 20, 'R', 'R');
      Junction(200, 200, 0.2, 20, 'R', 'r');
      Junction(200, 200, 0.2, 20, 'U', 'A');
      Junction(200, 200, 0.2, 30, 'L', 'L');
      Junction(200, 200, 0.5, 20, 'L', 'L');


      Junction(150, 150, 0.2, 100, 'M', 'c');
      Junction(100, 100, 0.2, 100, 'U', 'B');

      Junction(200, 200, 0.5, 20, 'M', 'c');
      Junction(200, 200, 0.5, 20, 'M', 's');


    }
    else if (Mode == 4) {
      //junior track
      //Path 3
      //Junction(LSpeed, RSpeed, P, D, juction, action );
      Junction(200, 200, 0.5, 20, 'M', 'c');
      Junction(200, 200, 0.5, 20, 'M', 'c');
      //Junction(150, 150, 0.2, 20, 'U', 'u');
      //Stop();
      // delay(10000);*/

      Junction(200, 200, 0.5, 20, 'R', 'R');
      Junction(200, 200, 0.5, 30, 'R', 'R');
      //C1
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Junction(150, 150, 0.5, 20, 'M', 'L');

      //C2

      Junction(200, 200, 0.5, 20, 'L', 'l');
      Junction(255, 255, 0.05, 10, 'M', 's');





      //Junction(100, 100, 0.2, 20, 'R', 's');

    }
  }
  else {
    Stop();
  }
}
