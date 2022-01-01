int error_old = 0;

void pid_line(int speedL_PID, int speedR_PID, float kp, float kd) {
  if (kp < 0.3) {
    lineFollowLeft();
  }
  else {
    int Position = get_line();

    if (Position > 4000) {
      turn_right(speedL_PID, speedR_PID, 0);
      //Serial.println("turn right");
      return;
    }
    else if (Position < 0) {
      turn_left(speedL_PID, speedR_PID, 0);
      //Serial.println("turn left");
      return;
    }

    int error = Position - 2000;
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

    forward(speedL_, speedR_);

    //Serial.println(String(Position) + " " + String(error) + " " + String(speed_correction) + " " + String(speedL_) +  " " + String(speedR_));
  }
}
