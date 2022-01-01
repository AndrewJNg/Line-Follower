/*int IR1 = A1;//left sensor                                                      //lower Qualifier
  int IR2 = A0;
  int IR3 = A3;
  int IR4 = A6;
  int IR5 = A7;//right sensor*/
/*int IR1 = A1;//left sensor                                                      //lower
  int IR2 = A2;
  int IR3 = A3;
  int IR4 = A6;
  int IR5 = A7;//right sensor*/
int button=4;
int IR0 = A0;
int IR1 = A1;                                                    //upper
int IR2 = A2;
int IR3 = A3;
int IR4 = A4;
int IR5 = A5;
int IR6 = A6;
int IR7 = A7;
void setup() {
  pinMode(button, INPUT);
  pinMode(IR0, INPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);
  pinMode(IR6, INPUT);
  pinMode(IR7, INPUT);
  Serial.begin(9600);
}

void loop() { 
  delay(1); 
  Serial.print(" button=");
  Serial.print(digitalRead(button));
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
