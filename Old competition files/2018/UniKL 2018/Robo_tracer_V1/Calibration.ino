void calibration(){
  
  
    int value=0;
    for(int i=1;i<7;i++){
      value=analogRead(IR[i]);
      if(minIR[i]>value){
        minIR[i]=value;
      }
      else if(maxIR[i]<value){
        maxIR[i]=value;
      }
      midIR[i] = ( minIR[i] + maxIR[i] ) * 0.5;
    }
  if(diagnose_calibrate==true){
    Serial.println("--------------------------------------------------");
    Serial.println("Calibrate min");
    Serial.println(" IR_1-" + String(minIR[0]) + " IR_2-" + String(minIR[1]) + " IR_3-" + String(minIR[2]) + " IR_4-" + String(minIR[3]) + " IR_5-" + String(minIR[4])+" IR_6-" +String(minIR[5]) + " IR_7-" + String(minIR[6]));
    Serial.println("Calibrate mid");
    Serial.println(" IR_1-" + String(midIR[0]) + " IR_2-" + String(midIR[1]) + " IR_3-" + String(midIR[2]) + " IR_4-" + String(midIR[3]) + " IR_5-" + String(midIR[4])+" IR_6-"+String(midIR[5]) + " IR_7-" + String(midIR[6]));
    Serial.println("Calibrate max");
    Serial.println(" IR_1-" + String(maxIR[0]) + " IR_2-" + String(maxIR[1]) + " IR_3-" + String(maxIR[2]) + " IR_4-" + String(maxIR[3]) + " IR_5-" + String(maxIR[4])+" IR_6-" +String(maxIR[5]) + " IR_7-" + String(maxIR[6]));
    Serial.println("--------------------------------------------------");
  }
 
}
