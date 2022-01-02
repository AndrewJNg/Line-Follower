/* junction(speedL, speedR, kp, kd, type, action, action_delay, turn_speed, turn_time);
 * This function is to let robot to decide what shold do on any junction. 
 * For example, the next junction type is middel and robot should turn right:
                junction(255, 255, 0.1, 0.2, 'M', 'r', 100, 128, 250);

   INSTRUCTION
   1. Left motor speed
      speedL_junction: not smaller than 0 and not bigger than 255

   2. Right motor speed
      speedR_junction: not smaller than 0 and not bigger than 255  

   3. PID gains kp
      tune by 0.05 increment or decrement until robot is able to perform line following smoothly
      
   4. PID gains kd
      tune by 0.05 increment or decrement until robot is able to perform line following smoothly
      
   5. Type of junction
      type: 'R' = right junction
            'M' = middle junction
            'L' =left junction

   6. What to do on the junction
      action: 'i' = ignore (ignore the junction and keep moving forward)
              'l' = turn left <--(small letter L) 
              'r' = turn right
              's' = stop

   7. Wait for a little bit before perform action to let robot exit and reenter junction smoothly
      action_delay: not smaller than 0 and bigger than 1000

   8. Robot turn speed
      turn_speed: not smaller than 100 and not bigger than 255

   9. Robot turn time
      turn_time: time taken for robot to turn 90 degree
*/ 
void junction(int speedL_junction, int speedR_junction, float kp, float kd, char type, char action, int action_delay, int turn_speed, int turn_time){
  switch (type){
   
    case 'LL':
             do{
               pid_line(speedL_junction, speedR_junction, kp, kd);
             }
             while(get_state[1] == 0 || get_state[1] == 0|| get_state[2] == 0);  // right junction xx111 
             forward(speedL_junction, speedR_junction);
             delay(action_delay);
             choose_action(action, turn_speed, turn_time);         
             break;
   case 'L':
             do{
             pid_line(speedL_junction, speedR_junction, kp, kd);
             }
             while(get_state[0] == 0 || get_state[2] == 0);  // left junction 111xx
             forward(speedL_junction, speedR_junction);
             delay(action_delay);
             choose_action(action, turn_speed, turn_time);         
             break;
   case 'M':
             do{
               pid_line(speedL_junction, speedR_junction, kp, kd);
             }
             while(get_state[1] == 0 || get_state[2] == 0 || get_state[3] == 0);  // middle junction 1xxx1
             forward(speedL_junction, speedR_junction);
             delay(action_delay);
             choose_action(action, turn_speed, turn_time);         
             break;
   case 'R':
             do{
               pid_line(speedL_junction, speedR_junction, kp, kd);
             }
             while(get_state[2] == 0 || get_state[4] == 0);  // right junction xx111 
             forward(speedL_junction, speedR_junction);
             delay(action_delay);
             choose_action(action, turn_speed, turn_time);         
             break;
    case 'RR':
             do{
               pid_line(speedL_junction, speedR_junction, kp, kd);
             }
             while(get_state[2] == 0 || get_state[3] == 0|| get_state[4] == 0);  // right junction xx111 
             forward(speedL_junction, speedR_junction);
             delay(action_delay);
             choose_action(action, turn_speed, turn_time);         
             break;
   default:
             break; 
  }
}

void choose_action(char action_, int turn_speed_, int turn_time_){
  switch(action_){
    case 'i': //ignore
              break;
    case 'l': //left
              turn_left(turn_speed_, turn_speed_, turn_time_);
              break;
    case 'r': //right
              turn_right(turn_speed_, turn_speed_, turn_time_);
              break;
    case 's': //stop
              Stop(); while(1);
              break;
    default:
              break;
  }
}

