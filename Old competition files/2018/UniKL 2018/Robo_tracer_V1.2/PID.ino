int error_old = 0;
int cummulative_error = 0;


void pid_line(int speedL_PID, int speedR_PID, float kp, float ki, float kd) {
  int Position = get_line();


  if (Position > 6000) {
    if (side == 1) {
      turn_right(200, 150, 0);
      //Serial.println("turn right");
      return;
    }
    else if (side == 0) {
      turn_left(150, 200, 0);
      //Serial.println("turn left");
      return;
    }
  }
  else if (Position < 000) {
    turn_left(150, 200, 0);
    //Serial.println("turn left");
    return; if (side == 1) {
      turn_right(200, 150, 0);
      //Serial.println("turn right");
      return;
    }
    else if (side == 0) {
      turn_left(150, 200, 0);
      //Serial.println("turn left");
      return;
    }
  }
  else {
    int error = Position - 3000;
    int speed_correction = (kp * error) + ( kd * (error - error_old) ) + ( ki * (cummulative_error));
    error_old = error;
    cummulative_error += error;
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

    forward(speedL_, speedR_);
  }
}