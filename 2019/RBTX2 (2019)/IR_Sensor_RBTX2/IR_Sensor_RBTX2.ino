
#include <HCSR04.h>
#define Echo 8
#define Trig 4

UltraSonicDistanceSensor distanceSensor(Trig, Echo);
int button1=2;
int button2=3;
int IR0 = A0;
int IR1 = A1;                                                    //upper
int IR2 = A2;
int IR3 = A3;
int IR4 = A4;
int IR5 = A5;
int IR6 = A6;
int IR7 = A7;
int LED = 13;
void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR7, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}
 
void loop() { 
  delay(1); 
  Serial.print(distanceSensor.measureDistanceCm());
  digitalWrite(LED,HIGH);
  Serial.print(" button1=");
  Serial.print(digitalRead(button1));
  Serial.print(" button2=");
  Serial.print(digitalRead(button2));
  Serial.print(" IR0=");
  Serial.print(analogRead(IR0));
  Serial.print(" IR1=");
  Serial.print(analogRead(IR1));
  Serial.print(" IR2=");
  Serial.print(analogRead(IR2));
  Serial.print(" IR3=");
  Serial.print(analogRead(IR3));
  Serial.print(" IR4=");
  Serial.print(analogRead(IR4));
  Serial.print(" IR5=");
  Serial.print(analogRead(IR5));
  Serial.print(" IR6=");
  Serial.print(analogRead(IR6));
  Serial.print(" IR7=");
  Serial.print(analogRead(IR7));
  Serial.println("");
}
