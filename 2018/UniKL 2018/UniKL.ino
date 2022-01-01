#include <SoftwareSerial.h>
SoftwareSerial bt(7,6);

boolean whiteLine = false;

boolean diagnose_bt = false;
boolean diagnose_position = false;
boolean diagnose_calibrate = false;

unsigned int minIR[]={1024,1024,1024,1024,1024};
unsigned int midIR[]={512,512,512,512,512};
unsigned int maxIR[]={0,0,0,0,0};
unsigned int get_state[]={0,0,0,0,0};

int IR[]={A2,A0,A3,A6,A7};        //infrared
int L[]={1,11,13,12,0};           //lights
int M[]={2,4};                    //motor
int P[]={3,5};                    //power
int B = 4;
void setup() {
  
  for(int i=0;i<5;i++){
    pinMode(IR[i],INPUT);
    pinMode(L[i],OUTPUT);  digitalWrite(L[i],LOW);
  }
  for(int i=0;i<2;i++){
    pinMode(M[i],OUTPUT);  digitalWrite(M[i],LOW);
    pinMode(P[i],OUTPUT);  digitalWrite(P[i],LOW); 
  }

  if(diagnose_bt == true || diagnose_position == true || diagnose_calibrate == true){
    Serial.begin(9600);
  }
  while(digitalRead(B)==LOW){
  }
}

void loop() {
//calibration(speedL, speedR, seconds);
  //calibration(255, 255, 2); //robot perform IR calibration before start line following
  
  
//  junction(speedL, speedR, kp  , kd  , type, action, action_delay, turn_speed, turn_time);

    pid_line(200, 200, 0.5, 0.5);
  
  while(1); // program stop here forever
}

