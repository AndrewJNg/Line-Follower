int last_pos = 2000, check_again = 0;

int get_line(){ 
  for(int i=0;i<5;i++){
    int valueIR=analogRead(IR[i]);
    delay(10);
    if(valueIR > midIR[i]){
      get_state[i] = 1;
    }
    else{
      get_state[i] = 0;
    }

    if(whiteLine){
      get_state[i] = 1 - get_state[i];
    }
  } 
  unsigned int sum_state = get_state[0] + get_state[1] + get_state[2] + get_state[3] + get_state[4];  
  if(sum_state == 0){
    check_again++;
    if(check_again > 8 && last_pos > 2100){
      return(5000);
    }
    else if(check_again > 8 && last_pos < 1900){
      return(-1);
    }
    else if(check_again>10){
      return(-1);
    }
    else{
      return(last_pos);
    }
  }
  check_again=0;
  
  unsigned int getPosition = (get_state[0]*0 + get_state[1]*1000 + get_state[2]*2000 + get_state[3]*3000 + get_state[4]*4000)/sum_state; 
  
  if(diagnose_position == true){
    Serial.println("--------------------------------------------------");
    Serial.println("IR position (on line = 1, off line = 0)");
    Serial.println("IR_1 || IR_2 || IR_3 || IR_4 || IR_5 || Position = " + String(getPosition));                              
    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4]));
    Serial.println("--------------------------------------------------");
  } 
  
  last_pos = getPosition;
  return(getPosition);
}
