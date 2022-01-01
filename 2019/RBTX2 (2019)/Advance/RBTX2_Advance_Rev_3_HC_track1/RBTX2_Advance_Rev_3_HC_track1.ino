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
unsigned int Mode = 4;
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
    }
    else if (Mode == 3) {
      Junction(150, 150, 0.2, 20, 'M', 'R');
      Junction(150, 150, 0.2, 20, 'R', 'r');
      Junction(150, 150, 0.2, 20, 'L', 'L');
      Junction(150, 150, 0.2, 20, 'M', 'L');
      Junction(150, 150, 0.2, 20, 'L', 'L');
      Junction(150, 150, 0.2, 20, 'M', 'cS');


    }
    else if (Mode == 4) {


      Junction(150, 150, 0.2, 20, 'M', 'c');
      Junction(150, 150, 0.2, 20, 'M', 'c');
      //Junction(150, 150, 0.2, 20, 'R', 'R');
      Forward(150, 150);
      delay(100);
      Right(150, 150);
      delay(170);
      do {
        Forward(150, 150);
      } while ((get_state[1] == 0) && (get_state[2] == 0) && (get_state[3] == 0));
      Forward(150, 150);
      delay(100);
      do {
        Right(150, 150);
      } while ((get_state[1] == 0));
      Junction(150, 150, 0.2, 20, 'R', 'R');
      Junction(150, 150, 0.2, 20, 'R', 'R');
      Junction(150, 150, 0.2, 20, 'M', 'R');
      Junction(150, 150, 0.2, 20, 'R', 'r');

      Junction(150, 150, 0.2, 20, 'R', 'i');
      Junction(150, 150, 0.2, 20, 'R', 's');







      //Junction(100, 100, 0.2, 20, 'R', 's');

    }
  }
  else {
    Stop();
  }
}
