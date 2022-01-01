
void choose_action(char action_, int speedL_junction_, int speedR_junction_, float kp_, float kd_) {
  switch (action_) {
    case 'i': //ignore
      do {
        PID(speedL_junction_, speedR_junction_, kp_, kd_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'L': //left
      leftTurn = 1;
      rightTurn = 0;
      do {
        Forward(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        Left(100, 100);
      } while (get_state[0] == 0);
      do {
        Left(100, 100);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      leftTurn = 0;
      break;


      case 'l': //left
      leftTurn = 1;
      rightTurn = 0;
      do {
        Forward(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        Left(0, 255);
      } while (get_state[0] == 0);
      do {
        Left(0, 255);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      leftTurn = 0;
      break;

      case 'T': //left
      do {
        Forward(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      do {
        Left(80, 80);
      } while (get_state[0] == 0);
      do {
        Left(80, 80);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      leftTurn = 0;
      break;


      case 'r': //right
      rightTurn = 1;
      leftTurn = 0;
      do {
        Forward(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        Right(255, 0);
      } while (get_state[4] == 0);
      do {
        Right(255, 0);
      } while ((get_state[3] == 0) || (get_state[4] == 1));
      rightTurn = 0;
      break;

    case 'R': //right
      rightTurn = 1;
      leftTurn = 0;
      do {
        Forward(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        Right(100, 100);
      } while (get_state[4] == 0);
      do {
        Right(100, 100);
      } while ((get_state[3] == 0) || (get_state[4] == 1));
      rightTurn = 0;
      break;


    case 's': //stop
      Stop();
      Start = false;
      Buzz(2, 100);
      break;


    case 'u': //ultrasonic
      Stop();
      delay(100);

      Right(0, 150);
      delay(400);
      Forward(200, 200);
      delay(200);
      do {
        Forward(100, 100);
      } while ((get_state[2] == 0));

      do {
        Right(100, 100);
      } while ((get_state[4] == 1));

      do {
        Right(100, 100);
      } while ((get_state[3] == 1) && (get_state[4] == 0));


      break;

    case 'A': //ultrasonic

      //whiteLine = !whiteLine ;

      Left(0, 200);
      delay(200);

        Forward(150, 150);
        delay(100);
       Right(200, 0);
         delay(400);
      do {
        Forward(150, 150);
      } while ((get_state[1] == 0) && (get_state[2] == 0) && (get_state[3] == 0));
      do {
        Forward(150, 150);
      } while ((get_state[1] == 1) || (get_state[2] == 1) || (get_state[3] == 1));
      
      break;

    case 'B': //ultrasonic

      //whiteLine = !whiteLine ;
      Forward(100, 100);
      delay(00);

      Left(0, 200);
      delay(300);
      Forward(255, 60);
      delay(300);

      do {
        Forward(255, 90);
      } while ( (get_state[4] == 0));
      do {
        Forward(150, 150);
      } while ( (get_state[2] == 0));

      do {
        Forward(150, 150);
      } while ( (get_state[0] == 1) || (get_state[4] == 1));


      break;

    case 'c': //change line
      whiteLine = !whiteLine ;


      break;


    default:
      break;
  }
}
