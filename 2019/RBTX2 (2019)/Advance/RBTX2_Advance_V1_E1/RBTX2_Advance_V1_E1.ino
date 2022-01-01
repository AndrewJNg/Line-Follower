/* eperiment 1 for RBTX_Advance
    turning test using pid instead of normal turn


    benafits: 1)may take courners faster
              2)may improve consistency

    problems left: consistency of scanning junctions
*/







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

int IR[] = { A2, A3, A4, A5, A6};

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
boolean rightTurn = 0;
boolean leftTurn = 0;

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
      // PID(255, 255, 1, 0);
      //Junction(speedL_junction, speedR_junction, kp, kd,action)
      /*Junction(255, 255, 0.5, 20, 'i');
      Junction(200, 200, 0.5, 20, 'i');
      Junction(200, 200, 0.5, 20, 'l');
      Junction(200, 200, 0.5, 20, 'l');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'r');
      Junction(200, 200, 0.5, 20, 'L');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'i');
      Junction(200, 200, 0.5, 20, 's');*/
      

      /*Junction(200, 200, 0.5, 20, 'L');
      Junction(100, 100, 0.8, 3 , 'l');
      Junction(200, 200, 0.5, 20, 'L');
      Junction(200, 200, 0.5, 20, 'L');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'L');
      Junction(200, 200, 0.5, 20, 'L');*/
      
      /*Junction(255, 255, 0.5, 20, 'c');
      
      Junction(100, 100, 0.8, 10, 'c');
      Junction(200, 200, 0.5, 20, 's');*/

      
      Junction(200, 200, 0.5, 20, 'r');
      Junction(200, 200, 0.5, 20, 'l');
      Junction(200, 200, 0.5, 20, 'L');
      Junction(200, 200, 0.5, 20, 'R');
      Junction(200, 200, 0.5, 20, 'i');
      Junction(200, 200, 0.5, 20, 's');
    }
    else if (Mode == 3) {
      updateEEPROM();
      
      digitalWrite(buzzer,LOW);
      digitalWrite(led,HIGH);
      do{PID(200, 200, 0.5, 1);
      }while((get_state[0] == 0) && (get_state[4] == 0));
      Stop();
      digitalWrite(led,LOW);
      digitalWrite(buzzer,HIGH);
     // rightTurn = 1;
      //PID(200, 200, 0.5, 1);

      /*do {
        PID(200, 200, 0.2, 2);
      } while ((get_state[0] == 1 ) || (get_state[4] == 1));
      Stop();
      delay(1000);*/
    }
    else if (Mode == 4) {
      updateEEPROM();
      PID(100, 100, 0.6, 10);
    }
  }


  else {
    Stop();
  }
}
