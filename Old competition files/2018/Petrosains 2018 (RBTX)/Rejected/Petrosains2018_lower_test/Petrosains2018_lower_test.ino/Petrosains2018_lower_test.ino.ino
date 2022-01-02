

// This is the library for the TB6612 that contains the class Motor and all the
// functions
#include <SparkFun_TB6612.h>
#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9//motor
#define BIN2 10
#define PWMB 11

const int offsetA = 1;
const int offsetB = 1;
Motor motorRight = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motorLeft = Motor(BIN1, BIN2, PWMB, offsetB, STBY);




int S = 500;




void setup()
{ 
  for (int x=0;x<4;x++){
   brake(motorLeft,motorRight);
      motorLeft.drive(255, S);//right

      brake(motorLeft, motorRight);
      delay(1000);
  }
}


void loop()
{

}
