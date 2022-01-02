void forward(int speedL, int speedR){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],HIGH);    //[0]HIGH      [1] HIGH
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);   //[0] speedL   [1] speedR 
}

void reverse(int speedL, int speedR){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],LOW);    //[0]LOW      [1] LOW
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);   //[0] speedL   [1] speedR 
}

void turn_left(int speedL, int speedR, int how_long){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],HIGH);    //[0]LOW      [1] HIGH
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);   //[0] speedL   [1] speedR 
  delay(how_long);
}

void turn_right(int speedL, int speedR, int how_long){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],LOW);    //[0]HIGH      [1] LOW
  analogWrite(P[0],speedL); analogWrite(P[1],speedR);  //[0] speedL   [1] speedR
  delay(how_long);
}

void Stop(){
  //analogWrite(P[0],0); analogWrite(P[1],0);  
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],HIGH);    //[0]HIGH      [1] LOW
  analogWrite(P[0],0); analogWrite(P[1],0);  //[0] speedL   [1] speedR
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Bforward(int speedL, int speedR){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],HIGH);    //[0]HIGH      [1] HIGH
  analogWrite(P[0],255); analogWrite(P[1],255);   //[0] speedL   [1] speedR 
}

void Breverse(int speedL, int speedR){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],LOW);    //[0]LOW      [1] LOW
  analogWrite(P[0],255); analogWrite(P[1],255);   //[0] speedL   [1] speedR 
}

void Bturn_left(int speedL, int speedR, int how_long){
  digitalWrite(M[0],LOW);  digitalWrite(M[1],HIGH);    //[0]LOW      [1] HIGH
  analogWrite(P[0],255); analogWrite(P[1],255);   //[0] speedL   [1] speedR 
  delay(how_long);
}

void Bturn_right(int speedL, int speedR, int how_long){
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],LOW);    //[0]HIGH      [1] LOW
  analogWrite(P[0],255); analogWrite(P[1],255);  //[0] speedL   [1] speedR
  delay(how_long);
}

void BStop(){
  //analogWrite(P[0],0); analogWrite(P[1],0);  
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],HIGH);    //[0]HIGH      [1] LOW
  analogWrite(P[0],0); analogWrite(P[1],0);  //[0] speedL   [1] speedR
}

