
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
        Left(100,200);
        //PID(100, 100, kp_, kd_);
      } while (get_state[2] == 0);
      leftTurn = 0;
      break;


    case 'L': //left
      leftTurn = 1;
      rightTurn = 0;
      do {
        //PID(100, 100, kp_, kd_);
        
        Left(100, 200);
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
        
        Right(180, 100);
        //PID(100, 100, kp_, kd_);
      } while (get_state[3] == 0);
      rightTurn = 0;
      break;



    case 'R': //right
      rightTurn = 1;
      leftTurn = 0;
      do {
        //PID(100, 100, kp_, kd_);
        Right(180, 100);
      } while (get_state[3] == 0);
      rightTurn = 0;
      break;


    case 's': //stop
      Stop();
      Start = false;
      Buzz(2, 100);
      break;


    case 'u': //ultrasonic
      Left(200,200);
      delay(100);
      Forward(200,200);
      delay(300);
      Stop();
      delay(1000);
      
      Right(200,200);
      delay(150);
      
      Stop();

      
      break;


    case 'c': //change line
      whiteLine = !whiteLine ;


      break;


    default:
      break;
  }
}
