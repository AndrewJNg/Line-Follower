unsigned int getPosition = 0;
int error_old = 0;

int last_pos = 200;


void PID(int speedL_PID, int speedR_PID, float kp, float kd) {
  scanLine();




  unsigned int sum_state = get_state[0] + get_state[1] + get_state[2] + get_state[3] + get_state[4];
  if (sum_state == 0)
  {
    if (last_pos >= 200) {
      //Stop();
      Right(speedL_PID, speedR_PID);
      //getPosition = 400;
      //turnright
      //last_pos = getPosition;
      Serial.println(String(getPosition));


    }
    else if (last_pos < 200) {
      // Stop();
      Left(speedL_PID, speedR_PID);
      //getPosition = 0;
      //turnleft
      //last_pos = getPosition;
      Serial.println(String(getPosition));

    }
  }

  else {


    getPosition = ((get_state[0] * 0) + (get_state[1] * 100) + (get_state[2] * 200) + (get_state[3] * 300) + (get_state[4] * 400)) / sum_state;


    //Serial.println("IR position (on line = 1, off line = 0)");

    Serial.println(String(get_state[0]) + " " + String(get_state[1]) + " " + String(get_state[2]) + " " + String(get_state[3]) + " " + String(get_state[4])  + " " + String(getPosition));
    last_pos = getPosition;



    int error = getPosition - 200;
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
  // Serial.println(String(Position) + " " + String(error) + " " + String(speed_correction) + " " + String(speedL_) +  " " + String(speedR_));
}
