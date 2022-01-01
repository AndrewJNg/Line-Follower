void forward(int speedL, int speedR){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],LOW);
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);  
}

void reverse(int speedL, int speedR){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],HIGH);
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);  
}

void turn_left(int speedL, int speedR, int how_long){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],LOW);
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);  
  delay(how_long);
}

void turn_right(int speedL, int speedR, int how_long){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],HIGH);
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);  
  delay(how_long);
}

void Stop(){
  analogWrite(P[0],0); analogWrite(P[1],0);  
}
