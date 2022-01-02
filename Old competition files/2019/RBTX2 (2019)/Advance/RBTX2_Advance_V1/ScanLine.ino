//ScanLine

void scanLine() {

  for (int i = 0; i < 5; i++) {
    int valueIR = analogRead(IR[i]);
    if (valueIR > midIR[i]) {
      get_state[i] = 1;
    }
    else {
      get_state[i] = 0;
    }
    // Serial.println(get_state[i]);

    if (whiteLine) {
      get_state[i] = 1 - get_state[i];
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
