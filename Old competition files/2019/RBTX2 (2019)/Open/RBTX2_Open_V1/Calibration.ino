//Calibration

boolean Update = false;

void calibration() {
  digitalWrite(led, LOW);
  int value = 0;
  for (int i = 0; i < 5; i++) {
    
    value = analogRead(IR[i]);
    if (minIR[i] > value) {
      minIR[i] = value;
    }
    else if (maxIR[i] < value) {
      maxIR[i] = value;
    }
    midIR[i] = ( minIR[i] + maxIR[i] ) * 0.5;
    Serial.print("  ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print(midIR[i]);
    
  }
  digitalWrite(led, HIGH);
  Serial.println();
  Update = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void updateEEPROM() {
  if (Update == true) {
    for (int i = 0; i < 5; i++) {
      EEPROM.update(i, (midIR[i] / 4));
      Serial.print( midIR[i], DEC);
      Serial.print( " ");
    }
    Update = false;
    Serial.println( );
  }
  else {

  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void readEEPROM() {
  for (int i = 0; i < 5; i++) {
    midIR[i] = EEPROM.read(i)*4;
    Serial.print( i);
    Serial.print(" = ");
    Serial.print( (midIR[i] ), DEC);
    Serial.print("  ");
  }

  Serial.println( );
}
