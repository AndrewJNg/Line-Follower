
#define PWMA 5
#define AIN2 6
#define AIN1 7
#define STBY 8
#define BIN1 9                                                  //motor 
#define BIN2 10
#define PWMB 11

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
go()
}

void brake(){
digitalWrite(STBY, HIGH);

digitalWrite(AIN1,HIGH);
digitalWrite(AIN2,HIGH);
analogWrite(PWMA,255);

digitalWrite(BIN1,HIGH);
digitalWrite(BIN2,HIGH);
analogWrite(PWMB,255);
    }

    
void go(){
digitalWrite(STBY, HIGH);

digitalWrite(AIN1,HIGH);
digitalWrite(AIN2,LOW);
analogWrite(PWMA,255);

digitalWrite(BIN1,HIGH);
digitalWrite(BIN2,LOW);
analogWrite(PWMB,255);
    }
