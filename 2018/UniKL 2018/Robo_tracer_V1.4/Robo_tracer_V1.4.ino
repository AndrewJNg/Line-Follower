boolean whiteLine = false;

boolean diagnose_bt = false;
boolean diagnose_position = false;
boolean diagnose_calibrate = false;
boolean diagnose_voltage = true;

unsigned int minIR[] = {1024, 1024, 1024, 1024, 1024, 1024, 1024};
unsigned int midIR[] = {512, 512, 512, 512, 512, 512, 512};
unsigned int maxIR[] = {0, 0, 0, 0, 0, 0, 0};
unsigned int get_state[] = {0, 0, 0, 0, 0, 0, 0};
int side=0;

int IR[] = {A1, A2, A3, A4, A5, A6, A7}; //infrared
int B = 4;
int led = 3;
int V = A0;    //voltage
boolean buttonState=false;

void setup() {
  Serial.begin(9600);
  for (int x = 0; x < 7; x++) {
    pinMode(IR[x], INPUT);
  }
  pinMode(led, OUTPUT); digitalWrite(led, LOW);
  pinMode(B,INPUT);
  while(digitalRead(B)==LOW){
  calibration();
  voltage_check();
  }
}

void loop() {   
 pid_line(150, 150, 0.2, 0.43, 0.5);

/*
    junction(150   , 150   , 0.08 , 0.5, 'M' , 'i'   , 0         , 0       , 0);

 
    junction(150   , 150   , 0.08 , 0.5, 'R' , 'r'   , 0         , 0       , 100);
    junction(150   , 150   , 0.08 , 0.5, 'R' , 'r'   , 0         , 0       , 100);  
    junction(150   , 150   , 0.08 , 0.5, 'L' , 'l'   , 0         , 0       , 100);
    junction(150   , 150   , 0.08 , 0.5, 'R' , 'r'   , 0         , 0       , 100);
    junction(150   , 150   , 0.08 , 0.5, 'L' , 'l'   , 0         , 0       , 100);
    junction(150   , 150   , 0.08 , 0.5, 'L' , 'l'   , 0         , 0       , 100);
*/
    
    



}
