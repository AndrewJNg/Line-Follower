//ScanLine

void scanLine() {

  for (int i = 0; i < 8; i++) {
    int valueIR = analogRead(IR[i]);

 get_state[i]=map(valueIR,minIR[i],maxIR[i],0,100);


    if (whiteLine) {
      get_state[i] = 100 - get_state[i];
    }

    if(get_state[i]>100){
      get_state[i]=0;
//    }
//  Serial.print(i);
//  Serial.print("  =  ");
//  Serial.print(get_state[i]);
//  Serial.print("    ");
  }

  }
  
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
