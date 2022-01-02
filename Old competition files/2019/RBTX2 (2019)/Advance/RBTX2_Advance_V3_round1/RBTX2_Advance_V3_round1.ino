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
unsigned int Mode = 2;
boolean Start = false;

//////////////////////////////////////////////////////////////////////////////////////////
boolean rightTurn = 0;
boolean leftTurn = 0;

boolean whiteLine = false;
int minSpeed = 170;
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
      Accel(200, 255, 0.5, 50, 30, 50);
      Straight(255, 255,1, 100,1400);
      Decel(255, 150, 0.5, 50, 30, 50);
      Buzz(1,100);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Accel(200, 255, 0.5, 50, 30, 50);
      Decel(255, 150, 0.5, 50, 30, 50);

      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(100, 100, 0.5, 50, 'L', 'L');
      Straight(255, 255, 0.5, 50, 500);
      Decel(255, 150, 0.5, 50, 30, 50);
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(100, 100, 0.5, 50, 'L', 'L');


      Stop();
      delay(100);
      Buzz(2, 50);
      //C1
      Junction(255, 255, 1, 100, 'L', 'i');
      Junction(255, 255, 1, 100, 'L', 'i');
      Junction(255, 255, 1, 100, 'R', 'i');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      //C2

      Buzz(3, 50);

      Junction(255, 255, 0.5, 50, 'M', 'c');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'i');
      Junction(255, 255, 0.5, 50, 'R', 'i');
      Junction(255, 255, 0.5, 50, 'M', 'c');
      Buzz(4, 50);

      //C3

      Junction(255, 255, 0.8, 50, 'R', 'r');
      Buzz(1, 50);
      Junction(200, 200, 1, 100, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.8, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 1, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'L', 'L');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      //      Buzz(1, 100);
      //      Stop();
      //      delay(4000);
      //C4
      Stop();
      delay(100);
      Buzz(3, 100);
      Accel(200, 255, 0.5, 20, 30, 10);
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Decel(255, 150, 0.5, 20, 15, 10);
      Junction(150, 150, 0.5, 20, 'U', 'A');
      Junction(255, 255, 0.5, 20, 'M', 's');
      // Stop();
      //delay(10000);
    }
    else if (Mode == 3) {
      Junction(150, 150, 0.5, 50, 'R', 'R');
      //            Accel(200, 255, 0.5, 50, 30, 50);
      //            Decel(255, 500, 0.5, 50, 30, 50);

      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(100, 100, 0.5, 50, 'L', 'L');
      Straight(255, 255, 0.5, 50, 500);
      Decel(255, 150, 0.5, 50, 30, 50);
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(100, 100, 0.5, 50, 'L', 'L');


      Stop();
      delay(100);
      Buzz(2, 50);
      //C1
      Junction(255, 255, 0.5, 50, 'L', 'i');
      Junction(255, 255, 0.5, 50, 'L', 'i');
      Junction(255, 255, 0.5, 50, 'R', 'i');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      //C2

      Buzz(3, 50);

      Junction(255, 255, 0.5, 50, 'M', 'c');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'i');
      Junction(255, 255, 0.5, 50, 'R', 'i');
      Junction(255, 255, 0.5, 50, 'M', 'c');
      Buzz(4, 50);

      //C3

      Junction(255, 255, 0.8, 50, 'R', 'r');
      Buzz(1, 50);
      Junction(200, 200, 1, 100, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.8, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 1, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'L', 'L');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      //      Buzz(1, 100);
      //      Stop();
      //      delay(4000);
      //C4
      Stop();
      delay(100);
      Buzz(3, 100);
      Accel(200, 255, 0.5, 20, 30, 10);
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Decel(255, 150, 0.5, 20, 15, 10);
      Junction(150, 150, 0.5, 20, 'U', 'A');
      Junction(255, 255, 0.5, 20, 'M', 's');
      // Stop();
      //delay(10000);
    }
    else if (Mode == 4) {
      Junction(150, 150, 0.5, 50, 'R', 'R');
      //            Accel(200, 255, 0.5, 50, 30, 50);
      //            Decel(255, 500, 0.5, 50, 30, 50);

      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(100, 100, 0.5, 50, 'L', 'L');
      Straight(255, 255, 0.5, 50, 500);
      Decel(255, 150, 0.5, 50, 30, 50);
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(100, 100, 0.5, 50, 'L', 'L');


      Stop();
      delay(100);
      Buzz(2, 50);
      //C1
      Junction(150, 150, 0.5, 50, 'L', 'i');
      Junction(200, 200, 0.5, 50, 'L', 'i');
      Junction(200, 200, 0.5, 50, 'R', 'i');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      //C2

      Buzz(3, 50);

      Junction(150, 150, 0.5, 50, 'M', 'c');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'L', 'i');
      Junction(150, 150, 0.5, 50, 'L', 'L');
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Junction(150, 150, 0.5, 50, 'R', 'i');
      Junction(150, 150, 0.5, 50, 'M', 'c');
      Buzz(4, 50);

      //C3

      Junction(255, 255, 0.8, 50, 'R', 'r');
      Buzz(1, 50);
      Junction(200, 200, 1, 100, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.8, 50, 'R', 'R');
      Buzz(1, 50);
      Junction(150, 150, 0.5, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 1, 50, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'L', 'L');
      Buzz(1, 100);
      Junction(150, 150, 0.5, 20, 'R', 'R');
      //      Buzz(1, 100);
      //      Stop();
      //      delay(4000);
      //C4
      Stop();
      delay(100);
      Buzz(3, 100);
      Accel(200, 255, 0.5, 20, 30, 10);
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Junction(255, 255, 0.5, 20, 'M', 'c');
      Decel(255, 150, 0.5, 20, 15, 10);
      Junction(150, 150, 0.5, 20, 'U', 'A');
      Junction(255, 255, 0.5, 20, 'M', 's');
      // Stop();
      //delay(10000);

      //Junction(100 0.2, 20, 'R', 's');

    }
  }
  else {
    Stop();
  }
}