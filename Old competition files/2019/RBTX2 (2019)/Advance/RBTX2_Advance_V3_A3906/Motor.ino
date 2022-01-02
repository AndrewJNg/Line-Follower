

void Forward(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);
  if(leftSpeed==0){
    
  analogWrite(BI2, 255);
  analogWrite(PWMB, 255);
  }
  else{
  analogWrite(BI2, leftSpeed);
  analogWrite(PWMB, 0);
  }

  if(rightSpeed==0){
    
  analogWrite(AI2, 255);
  analogWrite(PWMA, 255);
  }
  else{
  analogWrite(AI2, 0);
  analogWrite(PWMA, rightSpeed);
  }

}


void Left(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);
  if(leftSpeed==0){
  analogWrite(BI2, 255);
  analogWrite(PWMB, 255);
  }
  else{
  analogWrite(BI2, 0);
  analogWrite(PWMB, leftSpeed);
  }

  if(rightSpeed==0){
  analogWrite(AI2, 255);
  analogWrite(PWMA, 255);
  }
  else{
  analogWrite(AI2, 0);
  analogWrite(PWMA, rightSpeed);
  }



}

void Right(int leftSpeed, int rightSpeed) {
  digitalWrite(STBY, HIGH);
  if(leftSpeed==0){
  analogWrite(BI2, 255);
  analogWrite(PWMB, 255);
  }
  else{
  analogWrite(BI2, leftSpeed);
  analogWrite(PWMB, 0);
  }

  if(rightSpeed==0){
  analogWrite(AI2, 255);
  analogWrite(PWMA, 255);
  }
  else{
  analogWrite(AI2, rightSpeed);
  analogWrite(PWMA, 0);
  }



}
void Stop() {

  digitalWrite(STBY, LOW);

  analogWrite(BI2, 255);
  analogWrite(PWMB, 255);

  analogWrite(AI2, 255);
  analogWrite(PWMA, 255);
}
