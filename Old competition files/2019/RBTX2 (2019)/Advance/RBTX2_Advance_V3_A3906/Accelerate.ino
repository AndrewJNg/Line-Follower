void Accel(int int_Speed, int final_Speed, float kp, float kd, int accelTime, int accelSpeed) {
  unsigned long delayCheckTime = millis();
  for (int x = int_Speed; x < final_Speed; x += accelSpeed) {
    
    delayCheckTime = millis();
    if (x > final_Speed) {
      x = final_Speed;
    }
    
    do {
      PID(x, x, kp, kd);
      
Serial.print(delayCheckTime);

Serial.print("    ");
Serial.println(x);
    } while ((millis() - delayCheckTime) < accelTime);
    
  }
}



void Straight(int Left_Speed, int Right_Speed,float kp, float kd,int Time){


  unsigned long delayStartTime = millis();
  
  do {

    PID(Left_Speed, Right_Speed, kp, kd);

  } while ((millis() - delayStartTime) < Time);

  
}


void Decel(int int_Speed, int final_Speed, float kp, float kd, int accelTime, int decelSpeed) {
  unsigned long delayCheckTime = millis();
  for (int x = int_Speed; x > final_Speed; x -= decelSpeed) {
    if (x < final_Speed) {
      x = final_Speed;
    }

    do {
      PID(x, x, kp, kd);

    } while ((millis() - delayCheckTime) < accelTime);
    delayCheckTime = millis();

  }
}
