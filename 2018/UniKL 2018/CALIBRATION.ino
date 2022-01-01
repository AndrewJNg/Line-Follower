void calibration(){
  
  int count_calibrate=1;
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
}
