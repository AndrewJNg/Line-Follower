void lineFollowLeft() {
    if (get_state[2]==0) {
   //   turnRight();
    
  digitalWrite(M[0],HIGH);  digitalWrite(M[1],LOW);    //[0]HIGH      [1] LOW
  analogWrite(P[0],255); analogWrite(P[1],230);  //[0] speedL   [1] speedR
    }
    else if (get_state[2]==1) {
     // turnLeft();
     
  digitalWrite(M[0],LOW);  digitalWrite(M[1],HIGH);    //[0]LOW      [1] HIGH
  analogWrite(P[0],230); analogWrite(P[1],200);   //[0] speedL   [1] speedR 
    }
}
