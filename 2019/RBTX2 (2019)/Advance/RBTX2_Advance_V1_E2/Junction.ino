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
      while (get_state[1] == 0 || get_state[2] == 0 || get_state[3] == 0); // middle junction 1xxx1
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
      } while ((distanceSensor.measureDistanceCm() > 15) || (distanceSensor.measureDistanceCm() < 0));
      choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
      break;
    default:
      break;
  }
  /* do {
     PID(speedL_junction, speedR_junction, kp, kd);
    }
    while ((get_state[0] == 0) && (get_state[4] == 0));
    choose_action(action, speedL_junction,  speedR_junction, kp,  kd);
    Stop();
  */

}
void choose_action(char action_, int speedL_junction_, int speedR_junction_, float kp_, float kd_) {
  switch (action_) {
    case 'i': //ignore
      do {
        PID(speedL_junction_, speedR_junction_, kp_, kd_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'l': //left
      leftTurn = 1;
      rightTurn = 0;
      do {
        Left(speedL_junction_, speedL_junction_);
      } while (get_state[4] == 0);

      do {
        Left(speedL_junction_, speedL_junction_);
      } while (get_state[4] == 1);


      do {
        //Left(100,100);
        PID(100, 100, kp_, kd_);
      } while (get_state[2] == 0);
      leftTurn = 0;
      break;


    case 'L': //left
      leftTurn = 1;
      rightTurn = 0;
      do {
        PID(150, 150, kp_, kd_);
        //Right(100, 100);
      } while (get_state[1] == 0);
      leftTurn = 0;
      break;




    case 'r': //right
      rightTurn = 1;
      leftTurn = 0;
      do {
        Right(speedR_junction_, speedR_junction_);
      } while (get_state[0] == 0);

      do {
        Right(speedR_junction_, speedR_junction_);
      } while (get_state[0] == 1);
      do {
        PID(150, 150, kp_, kd_);
      } while (get_state[3] == 0);
      Buzz(1, 100);
      rightTurn = 0;
      break;



    case 'R': //right
      rightTurn = 1;
      leftTurn = 0;
      do {
        PID(150, 150, kp_, kd_);
        //Right(100, 100);
      } while (get_state[3] == 0);
      Buzz(1, 100);
      rightTurn = 0;
      break;


    case 's': //stop
      Stop();
      Start = false;
      Buzz(1, 100);
      break;


    case 'u': //ultrasonic
    //  Stop();
    //  delay(10000);
      Right(100,100);
      delay(250);
      do {
  Forward(100,100);
      } while ((get_state[1] == 0)&&(get_state[2] == 0)&&(get_state[3] == 0));
  //Forward(100,100);
    //  delay(100);
    //  Left(100,100);
    //  delay(100);
      Stop();/*
do{
  Forward(255,255);
}while((get_state[0] == 0)&&(get_state[1] == 0)&&(get_state[2] == 0)&&(get_state[3] == 0)&&(get_state[4] == 0));*/
      
      break;


    case 'c': //change line
      whiteLine = !whiteLine ;


      break;


    default:
      break;
  }
}
