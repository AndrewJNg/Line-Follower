void Junction(int speedL_junction, int speedR_junction, float kp, float kd,  char action)
{
  do {
    PID(speedL_junction, speedR_junction, kp, kd);
  }
  while ((get_state[0] == 0) && (get_state[4] == 0));
  choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
  Stop();


}
void choose_action(char action_, int speedL_junction_, int speedR_junction_, float kp_, float kd_) {
  switch (action_) {
    case 'i': //ignore
      do {
        PID(speedL_junction_, speedR_junction_, kp_, kd_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'l': //left
      do {
        Left(speedL_junction_, speedL_junction_);
      } while ((get_state[1] == 1)||(get_state[2] == 1)||(get_state[3] == 1));
      //do {
        //Left(speedL_junction_, speedL_junction_);
      //} while (get_state[0] == 0);
      do {
        Left(100, 100);
      } while (get_state[1] == 0);
      Buzz(1,100);
      break;


    case 'r': //right
      do {
        Right(speedR_junction_, speedR_junction_);
      } while ((get_state[1] == 1)||(get_state[2] == 1)||(get_state[3] == 1));
      //do {
        //Right(speedR_junction_, speedR_junction_);
      //} while (get_state[4] == 0);
      do {
        Right(100, 100);
      } while (get_state[3] == 0);
      Buzz(1,100);
      break;


    case 's': //stop
      Stop();
      Start = false;
      Buzz(1,100);
      break;


    case 'c': //change line
      Stop();
      whiteLine != whiteLine ;
      break;


    default:
      break;
  }
}
