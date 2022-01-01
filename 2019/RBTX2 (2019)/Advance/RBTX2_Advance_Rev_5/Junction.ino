unsigned int sum_state=0;
void Junction(int speedL_junction, int speedR_junction, float kp, float kd, char type, char action)
{ switch (type) {
    case 'L':
      do {
        PID(speedL_junction, speedR_junction, kp, kd);
      }
      while (get_state[0] == 0 ); // left junction 111xx
      choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
      break;
    case 'M':
      do {
        PID(speedL_junction, speedR_junction, kp, kd);
      }
      while (get_state[0] == 0 ||  get_state[4] == 0); // middle junction 1xxx1
      choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
      break;
    case 'R':
      do {
        PID(speedL_junction, speedR_junction, kp, kd);
      }
      while ( get_state[4] == 0); // right junction xx111
      choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
      break;
      
    case 'U':
      do {
        PID(speedL_junction, speedR_junction, kp, kd);
      } while (((distanceSensor.measureDistanceCm() > 25 ) || (distanceSensor.measureDistanceCm() < 0)));
      choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
      break;


    default:
      break;
  }

}
