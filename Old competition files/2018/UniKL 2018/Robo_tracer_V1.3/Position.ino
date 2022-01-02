int last_pos = 3000, check_again = 0;

int get_line(){ 
  for(int i=0;i<7;i++){
    int valueIR=analogRead(IR[i]);
    if(valueIR > midIR[i]){
      get_state[i] = 1;             //get_state[i]=1      means white
    }
    else{
      get_state[i] = 0;            //get_state[i]=0      means black
    }

    if(whiteLine){                        
      get_state[i] = 1 - get_state[i];          
    }                                           
  } 
  unsigned int sum_state = get_state[0]+ get_state[1] + get_state[2] + get_state[3] + get_state[4] + get_state[5] + get_state[6];  
  if(sum_state == 0){    //all white
    check_again++;
    if(check_again > 8 && last_pos > 3000){             
      return(7000);
    }
    else if(check_again > 8 && last_pos < 3000){
      return(-1);
    }
    else if(check_again>10){
      return(7000);
    }
    else{
      return(last_pos);                            
    } 
  }
  else if (sum_state == 5){
    Stop();
  }
  check_again=0;
  
  unsigned int getPosition = ( get_state[0]*0 +get_state[1]*1000 + get_state[2]*2000 + get_state[3]*3000 + get_state[4]*4000 + get_state[5]*5000+ get_state[6]*6000)/sum_state; 
 
  if(diagnose_position == true){
    Serial.println("--------------------------------------------------");
    Serial.println("IR position (on line = 1, off line = 0)");
    Serial.println("IR_1 || IR_2 || IR_3 || IR_4 || IR_5 || Position = " + String(getPosition));                              
    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])+ " " + String(get_state[5])+ " " + String(get_state[6]));
    Serial.println("--------------------------------------------------");
  } 
  
  last_pos = getPosition;
  return(getPosition);
}
