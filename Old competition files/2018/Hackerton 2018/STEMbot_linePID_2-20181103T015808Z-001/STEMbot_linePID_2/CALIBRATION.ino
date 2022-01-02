void calibration(int speedL_calibration, int speedR_calibration, int how_many){
  for(int i=1;i<4;i++){
    digitalWrite(L[i],HIGH);
    delay(700);  //delay(700);
  }
  
  turn_right(speedL_calibration, speedR_calibration,0);
  int count_calibrate=1;
  do{
    int value=0;
    for(int i=0;i<5;i++){
      value=analogRead(IR[i]);
      delay(10);
      if(minIR[i]>value){
        minIR[i]=value;
      }
      else if(maxIR[i]<value){
        maxIR[i]=value;
      }
      midIR[i] = ( minIR[i] + maxIR[i] ) * 0.5;
    }
    count_calibrate++;
  }
  while(count_calibrate < how_many*20);
  Stop();

  if(diagnose_calibrate==true){
    Serial.println("--------------------------------------------------");
    Serial.println("Calibrate min");
    Serial.println("IR_1 = " + String(minIR[0]) + "IR_2 = " + String(minIR[1]) + "IR_3 = " + String(minIR[2]) + "IR_4 = " + String(minIR[3]) + "IR_5 = " + String(minIR[4]));
    Serial.println("Calibrate mid");
    Serial.println("IR_1 = " + String(midIR[0]) + "IR_2 = " + String(midIR[1]) + "IR_3 = " + String(midIR[2]) + "IR_4 = " + String(midIR[3]) + "IR_5 = " + String(midIR[4]));
    Serial.println("Calibrate max");
    Serial.println("IR_1 = " + String(maxIR[0]) + "IR_2 = " + String(maxIR[1]) + "IR_3 = " + String(maxIR[2]) + "IR_4 = " + String(maxIR[3]) + "IR_5 = " + String(maxIR[4]));
    Serial.println("--------------------------------------------------");
  }
  BStop();
  for(int i=1;i<4;i++){
    digitalWrite(L[i],LOW);
    delay(50);
  }
}
