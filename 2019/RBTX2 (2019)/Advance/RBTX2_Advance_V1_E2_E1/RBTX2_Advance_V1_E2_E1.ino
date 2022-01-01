
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
unsigned int get_state[] = {0, 0, 0, 0, 0};

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

void loop() {
  LDRF();
  IRSF();
  Buzzer();
  Button();

  if (Start) {
    if (Mode == 1) {
      calibration();
    }
    else if (Mode == 2) {
      /*Junction(200, 200, 0.5, 20,'L', 'l');
        Junction(200, 200, 0.5, 20,'L', 'l');
        Junction(200, 200, 0.5, 20,'M', 'R');
        Junction(200, 200, 0.5, 20,'M', 'R');
        Junction(200, 200, 0.5, 20,'R', 'r');
        Junction(200, 200, 0.5, 20,'R', 'i');
        Junction(200, 200, 0.5, 20,'M', 'L');
        Junction(200, 200, 0.5, 20,'L', 'i');
        Junction(200, 200, 0.5, 20,'L', 's');*/
      Junction(200, 200, 0.5, 20, 'R', 'r');
      Junction(200, 200, 0.5, 20, 'L', 'l');
      Junction(200, 200, 0.5, 20, 'M', 'R');
      Junction(200, 200, 0.5, 20, 'M', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'i');
      Junction(200, 200, 0.5, 20, 'M', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'i');
      Junction(200, 200, 0.5, 20, 'R', 'i');
      Junction(200, 200, 0.5, 20, 'R', 's');
    }

    else if (Mode == 3) {
      Junction(200, 200, 0.5, 20, 'M', 'R');
      Junction(200, 200, 0.5, 20, 'R', 'R');
      Junction(200, 200, 0.5, 20, 'L', 'L');
      Junction(200, 200, 0.5, 30, 'L', 'L');
      Junction(150, 150, 0.4, 30, 'L', 'L');
      Junction(150, 150, 0.5, 30, 'L', 'L');
      Junction(150, 150, 0.5, 20, 'M', 'c');
      Junction(100, 100, 0.5, 20, 'M', 'c');
      Junction(200, 200, 0.5, 20, 'M', 's');
    }
    else if (Mode == 4) {

      Junction(255, 255, 0.2, 20,'M', 'c');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20,'M', 'c');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20,'U', 'u');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20,'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20,'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 20,'R', 'R');
      Buzz(1, 200);
      Junction(255, 255, 1, 30,'L', 'L');
      Buzz(1, 200);
      Junction(255, 255, 0.5, 30,'L', 'l');
      Buzz(1, 200);
      Junction(255, 255, 0.4, 5,'M', 's');
    }
  }
  else {
    Stop();
  }
}
