#include <SoftwareSerial.h>
SoftwareSerial bt(7,6);

boolean whiteLine = false;

boolean diagnose_bt = true;
boolean diagnose_position = false;
boolean diagnose_calibrate = false;

unsigned int minIR[]={1024,1024,1024,1024,1024};
unsigned int midIR[]={512,512,512,512,512};
unsigned int maxIR[]={0,0,0,0,0};
unsigned int get_state[]={0,0,0,0,0};

int IR[]={A7,A6,A2,A1,A0};
int L[]={1,11,13,12,0};
int M[]={2,4};
int P[]={3,5};

void setup() {
  bt.begin(9600);
  bt.print("AT+NAME=nurul\r\n");
  
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
}

void loop() {
//bt_control(speedL, speedR);
  bt_control(128, 128); //robot starts with BT control mode until 'auto' button is press

//calibration(speedL, speedR, seconds);
  calibration(200, 200, 3); //robot perform IR calibration before start line following
  
  do{ //students must modify here to perform desired decision on junctions
//  junction(speedL, speedR, kp, kd, type, action, action_delay, turn_speed, turn_time);
    junction(255, 255, 0.2, 0.35, 'L', 'l', 275, 200, 425);
    junction(255, 255, 0.2, 0.35, 'M', 'l', 275, 200, 425);
    junction(255, 255, 0.2, 0.35, 'L', 'i', 275, 200, 425);
    junction(255, 255, 0.2, 0.35, 'L', 'l', 275, 200, 425);
    junction(255, 255, 0.2, 0.35, 'R', 'r', 275, 200, 425);
    junction(255, 255, 0.2, 0.35, 'M', 's', 100, 200, 425);
  }
  while(1); // program stop here forever
}

