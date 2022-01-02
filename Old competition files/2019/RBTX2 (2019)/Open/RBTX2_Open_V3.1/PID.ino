
unsigned int getPosition = 0;
int error_old = 0;
int check_again = 0;
int last_pos = 200;


void PID(int speedL_PID, int speedR_PID, float kp, float kd) {

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




  sum_state = get_state[0] + get_state[1] + get_state[2] + get_state[3] + get_state[4] + get_state[5] + get_state[6];
  if (sum_state == 0)
  {
    check_again++;
    if ( last_pos >= 200) {

      //      Right(0 , 0 );
      Right(speedL_PID , speedR_PID );
    }


    else if ( last_pos < 200) {

      Left(speedL_PID , speedR_PID );
      //      Left(0, 0 );

    }
  }
  else if (get_state[1] || get_state[5]) {
if(startPID==false){

    if (get_state[1] && get_state[5] == 0) {
      do {
        Left(150, 150);
      } while (get_state[1] == 0);
      do {
        Left(150, 150);
      } while ((get_state[1] == 1) || (get_state[2] == 0));
    }

    else if (get_state[1] == 0 && get_state[6]) {
      do {
        Right(150, 150);
      } while (get_state[5] == 0);
      do {
        Right(150, 150);
      } while ((get_state[4] == 0) || (get_state[5] == 1));
    }
    else if (get_state[1] && get_state[6]) {

      Forward(speedL_PID , speedR_PID);
    }
}
    }
    else {


      getPosition = ((get_state[0] * 0) + (get_state[1] * 100) + (get_state[2] * 200) + (get_state[3] * 300) + (get_state[4] * 400) + (get_state[5] * 500) + (get_state[6] * 600)) / sum_state;


      //Serial.println("IR position (on line = 1, off line = 0)");

      // Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])  + " " + String(getPosition));
      last_pos = getPosition;



      int error = getPosition - 300;
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

    }
    Serial.println(String(getPosition) );
  }
