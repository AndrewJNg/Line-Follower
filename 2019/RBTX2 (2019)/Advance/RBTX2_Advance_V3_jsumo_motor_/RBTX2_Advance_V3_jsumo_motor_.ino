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

//Mode 0.4       caLibration Mode
//Mode 2       speed 1
//Mode 3       speed 2
//Mode 4       speed 3


//////////////////////////////////////////////////////////////////////////////////////////

//unsigned Long currentMiLLis = 0;
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
      //caLibration
      calibration();
    }
    else if (Mode == 2) {
      
//            Accel(70, 0, 0.6, 20, 60, 10);
//            Straight(30, 30, 0.1, 1, 450, 5000);
//            Decel(160, 60, 0.6, 20, 60, 10);

            Junction(50, 50, 0.1, 1, 450, 'R', 'R');
            Buzz(1, 100);
            
            Junction(50, 50, 0.1, 1, 450, 'R', 'R');
           /* Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'R', 'i');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'L', 'L');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'L', 'i');
            Stop();
            delay(1000);*/
            //Buzz(1, 100);
        
//            Accel(70, 160, 0.3, 20, 20, 10);
//            Decel(160, 60, 0.3, 20, 20, 10);


/*
            Junction(30, 30, 0.1, 1, 450, 'R', 'R');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'R', 'R');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'L', 'L');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'R', 'i');
            Buzz(1, 100);
            // Straight(60, 60, 0.4, 20, 20);
            //DeceL(255, 0.450, 0.4, 20, 30, 20);
            Junction(30, 30, 0.1, 1, 450, 'L', 'L');
            Buzz(1, 100);
            Junction(30, 30, 0.1, 1, 450, 'L', 'L');
            //Buzz(2, 30);
            


            //C1
/*
            Junction(60, 60, 0.8, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'R', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'L', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'R', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'L', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'R', 'R');
            Buzz(1, 100);

            //C2

            Junction(80, 80, 0.6, 20, 'M', 'c');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'L', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'R', 'R');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'R', 'i');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'M', 'c');
            Buzz(1, 100);
            //C3

            //Junction(60, 60, 0.2, 20, 'R', 'R');

            Accel(60, 150, 0.3, 20, 60, 10);
            Junction(150, 150, 0.3, 20, 'R', 'i');
            Buzz(1, 100);
            Decel(150, 50, 0.3, 20, 30, 10);
            Junction(50, 50, 0.6, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(50, 50, 0.6, 20, 'R', 'R');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'R', 'R');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'R', 'R');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(60, 60, 0.8, 20, 'R', 'R');
            Buzz(1, 100);
            //C4


            Straight(60, 60, 0.6, 20, 100);
            Accel(60, 150, 0.3, 20, 60, 10);
            Junction(150, 150, 0.3, 20, 'M', 'c');
            Buzz(1, 100);
            Junction(150, 150, 0.3, 20, 'M', 'c');
            Buzz(1, 100);
            Decel(150, 60, 0.3, 20, 30, 10);
            Junction(60, 60, 0.6, 20, 'R', 'R');
            Buzz(1, 100);
            Junction(60, 60, 0.6, 20, 'L', 'L');
            Buzz(1, 100);
            Junction(150, 150, 0.6, 20, 'M', 's');
            Buzz(1, 100);*/
             Stop();
            delay(10000);



//        PID(30, 30, 0.1, 1, 450);
       // PID(50, 50, 0.05, 1, 250);
    }
    else if (Mode == 3) {

        PID(50, 50, 0.005, 1, 300);
    }
    else if (Mode == 4) {
        PID(50, 50, 0.0005, 1, 450);
    }
  }
  else {
    Stop();
  }
}
