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

int IR[]={A7,A6,A2,A1,A0};        //infrared
int L[]={1,11,13,12,0};           //lights
int M[]={2,4};                    //motor
int P[]={3,5};                    //power

void setup() {
  bt.begin(9600);
  bt.print("AT+NAME=AndrewJNg\r\n");
  
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
  bt_control(255, 255); //robot starts with BT control mode until 'auto' button is press

//calibration(speedL, speedR, seconds);
  calibration(255, 255, 2); //robot perform IR calibration before start line following
  
  do{ //students must modify here to perform desired decision on junctions
    for(int i=0;i<5;i++){
    digitalWrite(L[i],LOW); 
  }
  
//  junction(speedL, speedR, kp  , kd  , type, action, action_delay, turn_speed, turn_time);

    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //1
    digitalWrite(11,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //2
    digitalWrite(13,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //3
    digitalWrite(12,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'M' , 'l'   , 275         , 255       , 425);   //4
    digitalWrite(11,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'M' , 'l'   , 275         , 255       , 425);   //5
    digitalWrite(13,LOW);
    junction(0   , 0   , 0.2 , 0.35, 'L' , 'l'   , 275         , 255       , 425);   //6
    digitalWrite(12,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //7
    digitalWrite(11,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'M' , 'l'   , 275         , 255       , 425);   //8
    digitalWrite(13,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //9
    digitalWrite(12,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //10
    digitalWrite(11,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //11
    digitalWrite(13,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'i'   , 275         , 255       , 425);   //12
    digitalWrite(12,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //13
    digitalWrite(11,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //14
    digitalWrite(13,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'i'   , 275         , 255       , 425);   //15
    digitalWrite(12,LOW);
    junction(255   , 255   , 0.2 , 0.35, 'R' , 'r'   , 275         , 255       , 425);   //16
    digitalWrite(11,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'L' , 'i'   , 275         , 255       , 425);   //17
    digitalWrite(13,HIGH);
    junction(255   , 255   , 0.2 , 0.35, 'L' , 'l'   , 275         , 255       , 425);   //18
    digitalWrite(12,HIGH);
    junction(0     , 0     , 0.2 , 0.35, 'M' , 's'   , 275         , 255       , 425);   //19
    digitalWrite(11,LOW);
  }
  while(1); // program stop here forever
}

