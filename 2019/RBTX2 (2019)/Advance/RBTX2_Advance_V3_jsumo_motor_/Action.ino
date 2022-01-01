
void choose_action(char action_, int speedL_junction_, int speedR_junction_, float kp_, float ki_, float kd_) {
  switch (action_) {
    case 'i': //ignore
      do {
        PID(speedL_junction_, speedR_junction_, kp_, ki_, kd_);
        //Forward(speedL_junction_, speedR_junction_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'L': //left
      do {
        Forward(50, 50);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      do {
        Left(100, 30);
      } while (get_state[0] == 0);
      do {
        Left(30, 30);
      } while ((get_state[0] == 1) || (get_state[1] == 0));
      Right(100, 100);
      delay(100);

      break;



    case 'R': //right
      do {
        Forward(50, 50);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


        Right(100, 100);
        delay(100);
      do {
        Right(30, 0);
      } while (get_state[4] == 0);
      do {
        Right(20, 0);
      } while (get_state[3] == 0 || get_state[4] == 1);
      /*
            do {
              if ((get_state[3] == 1) ||(get_state[4] == 1)) {
                Right(30, 30);
              }
              else if ((get_state[1] == 1) ||(get_state[0] == 1))  {
                Left(30, 30);
              }
            } while ((get_state[0] == 1)|| (get_state[4] == 1));*/
      //      Left(30,0);
      //      delay(100);
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

      Right(200, 00);
      delay(150);

      //  Forward(150, 150);
      //  delay(300);
      // Right(200, 0);
      //   delay(350);
      do {
        Forward(150, 150);
      } while ((get_state[1] == 0) && (get_state[2] == 0) && (get_state[3] == 0));
      do {
        Forward(150, 150);
      } while ((get_state[1] == 1) || (get_state[2] == 1) || (get_state[3] == 1));
      do {
        Right(150, 150);
      } while (get_state[2] == 0 );

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
