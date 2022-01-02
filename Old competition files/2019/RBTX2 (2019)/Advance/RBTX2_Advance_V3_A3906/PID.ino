
unsigned long getPosition = 0;
int error_old = 0;
int check_again = 0;
int last_pos = 200;


void PID(int speedL_PID, int speedR_PID, float kp, float kd) {

  updateEEPROM();
  scanLine();





   sum_state = (get_state[0] + get_state[1] + get_state[2] + get_state[3] + get_state[4]+ get_state[5]+ get_state[6])/100;
  /*if (sum_state == 0)
  {
    check_again++;
    if ( last_pos >= 2) {
      Stop();
      //if(straightline==0){
        
//      Right(speedL_PID, speedR_PID );
     // }
     // else if (straightline==1){
        
    //Forward(speedL_PID, speedR_PID);
     // }
      
    //Forward(100,100);
      //Serial.println(String(getPosition));
    }

    
    else if ( last_pos < 2) {
       Stop();
      //if(straightline==0){
        
//      Left(speedL_PID, speedR_PID);
     // }
      
     // else if (straightline==1){
        
    //Forward(speedL_PID, speedR_PID);
   //   }
      
    //Forward(100, 100);
     // Serial.println(String(getPosition));

    }
  }*/
//  else {


    getPosition = ((get_state[0] * 1) + (get_state[1] * 2) + (get_state[2] * 3) + (get_state[3] * 4) + (get_state[4] * 5)+ (get_state[5] * 6)+ (get_state[6] * 7)) / sum_state;
//    if(getPosition>65000){
//      getPosition=0;
//    }
    
//    getPosition = ((get_state[0] * 1) + (get_state[1] * 2) + (get_state[2] * 3) + (get_state[3] * 4) + (get_state[4] * 5)) / sum_state);


    //Serial.println("IR position (on line = 1, off line = 0)");
//Serial.println(getPosition);
//    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4]) + " " + String(get_state[5]) + " " + String(get_state[6])  + " " + String(getPosition));
//    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])  + " " + String(getPosition));
    last_pos = getPosition;



    long error = getPosition - 400;
    int speed_correction = kp * error + kd * (error - error_old);
    error_old = error;

    int speedL_ = speedL_PID + speed_correction;
    if (speedL_ < 0) {
      speedL_ = 0;
    }
    else if (speedL_ > 255) {
      speedL_ = 255;
    }

    int speedR_ = speedR_PID - speed_correction;
    if (speedR_ < 0) {
      speedR_ = 0;

    }
    else if (speedR_ > 255) {
      speedR_ = 255;
    }

    Forward(speedL_, speedR_);

//  }

    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4]) + " " + String(get_state[5]) + " " + String(get_state[6])  + " " + String(error));

}
