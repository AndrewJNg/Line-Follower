
unsigned int getPosition = 0;
int error_old = 0;
int check_again = 0;
int last_pos = 200;
int cummulative=0;

void PID(int speedL_PID, int speedR_PID, float kp, float ki, float kd) {

  updateEEPROM();
  scanLine();

  if (rightTurn == 1) {
    get_state[0] = 0;
    get_state[1] = 0;
    last_pos = 400;
  }
  if (leftTurn == 1) {
    get_state[3] = 0;
    get_state[4] = 0;
    last_pos = 0;
  }




  sum_state = get_state[0] + get_state[1] + get_state[2] + get_state[3] + get_state[4];
  if (sum_state == 0)
  {
    check_again++;
    if ( last_pos >= 200) {
      //Stop();
      //if(straightline==0){

      Right(30,30);
      // }
      // else if (straightline==1){

      //Forward(speedL_PID, speedR_PID);
      // }

      //Forward(100,100);
      //Serial.println(String(getPosition));
    }


    else if ( last_pos < 200) {
      // Stop();
      //if(straightline==0){

      Left(30,30);
      // }

      // else if (straightline==1){

      //Forward(speedL_PID, speedR_PID);
      //   }

      //Forward(100, 100);
      // Serial.println(String(getPosition));

    }
  }
  else {


    getPosition = ((get_state[0] * 0) + (get_state[1] * 100) + (get_state[2] * 200) + (get_state[3] * 300) + (get_state[4] * 400)) / sum_state;


    //Serial.println("IR position (on line = 1, off line = 0)");

    // Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])  + " " + String(getPosition));
    last_pos = getPosition;



    int error = getPosition - 200;
    cummulative = cummulative+error;
    int speed_correction = kp * error  + (kd * (error - error_old));//+ ki*(cummulative)
    error_old = error;

    int speedL_ = speedL_PID + speed_correction;
    if (speedL_ < 0) {
      speedL_ = 0;
    }
    else if (speedL_ > 100) {
      speedL_ = 100;
    }

    int speedR_ = speedR_PID - speed_correction;
    if (speedR_ < 0) {
      speedR_ = 0;

    }
    else if (speedR_ > 100) {
      speedR_ = 100;
    }

    Forward(speedL_, speedR_);

  }
  // Serial.println(String(Position) + " " + String(error) + " " + String(speed_correction) + " " + String(speedL_) +  " " + String(speedR_));
}
