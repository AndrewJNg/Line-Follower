int Black1=250;
int Black2=250;
int Black3=250;

int White1=250;
int White2=250;
int White3=250;

int Average1=250;
int Average2=250;
int Average3=250;

int IR1 = A5;//left sensor                                                      //pin
int IR2 = A4;
int IR3 = A3;//right sensor
void setup() {
  // put your setup code here, to run once:
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.print(" Black1=");
  Serial.print(Black1);
  Serial.print(" White1=");
  Serial.print(White1);
  Serial.print(" Black2=");
  Serial.print(Black2);
  Serial.print(" White2=");
  Serial.print(White2);
  Serial.print(" Black3=");
  Serial.print(Black3);
  Serial.print(" White3=");
  Serial.print(White3);
  
  Serial.println("            ");

 if (analogRead(IR1)>Black1){
  Black1=analogRead(IR1);
 }
 if (analogRead(IR1)<White1){
  White1=analogRead(IR1);
 }
 if (analogRead(IR2)>Black2){
  Black2=analogRead(IR2);
 }
 if (analogRead(IR2)<White2){
  White2=analogRead(IR2);
 }
 if (analogRead(IR3)>Black3){
  Black3=analogRead(IR3);
 }
 if (analogRead(IR3)<White3){
  White3=analogRead(IR3);
 }

  
}
