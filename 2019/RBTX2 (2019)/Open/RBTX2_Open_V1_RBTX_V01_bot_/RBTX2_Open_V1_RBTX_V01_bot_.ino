#include <EEPROM.h>

#define PWMA 5
#define AI2 6
#define AI1 7
#define STBY 8
#define BI1 9
#define BI2 10
#define PWMB 11

//////////////////////////////////////////////////////////////////////////////////////////
#define bStart 2
#define bAdd 3
#define bMinus 0
#define buzzer 12
#define led 13

//////////////////////////////////////////////////////////////////////////////////////////

int IR[] = { A0, A1, A2, A3, A4};

unsigned int minIR[] = {1024, 1024, 1024, 1024, 1024};
unsigned int midIR[] = {512, 512, 512, 512, 512};
unsigned int maxIR[] = {0, 0, 0, 0, 0};
unsigned int get_state[] = {0, 0, 0, 0, 0};

//Mode 1       calibration Mode
//Mode 2       speed 1
//Mode 3       speed 2
//Mode 4       speed 3


//////////////////////////////////////////////////////////////////////////////////////////

unsigned long currentMillis = 0;
unsigned int Mode = 2;
boolean Start = false;

//////////////////////////////////////////////////////////////////////////////////////////


boolean whiteLine = false;

void loop() {
  currentMillis = millis();
  Buzzer();
  Button();

  if (Start) {
    if (Mode == 1) {
      calibration();
    }
    else if (Mode == 2) {
      updateEEPROM();
      //PID(int speedL_PID, int speedR_PID, float kp, float kd);
      // PID(100, 100, 0.2, 0);
      PID(205, 205, 0.0005, 4);
    }
    else if (Mode == 3) {
      PID(205, 205, 0.0005,4);
    }
    else if (Mode == 4) {
      //PID(255, 255, 0.2, 0);
      PID(205, 205, 0.0005, 4);
    }
  }


  else {
    Stop();
  }



}
