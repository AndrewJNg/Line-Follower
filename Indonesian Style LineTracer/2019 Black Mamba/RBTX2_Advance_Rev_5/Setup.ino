//Setup

void setup() {
  Serial.begin(9600);
  pinMode(bStart, INPUT);
  pinMode(bMode, INPUT);
  pinMode(buzzer, OUTPUT); digitalWrite(buzzer, LOW);
  pinMode(led, OUTPUT); digitalWrite(led, HIGH);


  pinMode(PWMA, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(STBY, OUTPUT); digitalWrite(STBY, LOW);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  readEEPROM();
}
