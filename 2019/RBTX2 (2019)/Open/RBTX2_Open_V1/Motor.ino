

void Forward(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);

  digitalWrite(BI2, HIGH);
  digitalWrite(BI1, LOW);
  analogWrite(PWMB, leftSpeed);

  digitalWrite(AI2, HIGH);
  digitalWrite(AI1, LOW);
  analogWrite(PWMA, rightSpeed);

}


void Left(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);

  digitalWrite(BI2, LOW);
  digitalWrite(BI1, HIGH);
  analogWrite(PWMB, leftSpeed);

  digitalWrite(AI2, HIGH);
  digitalWrite(AI1, LOW);
  analogWrite(PWMA, rightSpeed);

}

void Right(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);

  digitalWrite(BI2, HIGH);
  digitalWrite(BI1, LOW);
  analogWrite(PWMB, leftSpeed);

  digitalWrite(AI2, LOW);
  digitalWrite(AI1, HIGH);
  analogWrite(PWMA, rightSpeed);


}
void Stop() {

  digitalWrite(STBY, LOW);

  digitalWrite(BI2, HIGH);
  digitalWrite(BI1, HIGH);
  analogWrite(PWMB, 0);

  digitalWrite(AI2, HIGH);
  digitalWrite(AI1, HIGH);
  analogWrite(PWMA, 0);
}
