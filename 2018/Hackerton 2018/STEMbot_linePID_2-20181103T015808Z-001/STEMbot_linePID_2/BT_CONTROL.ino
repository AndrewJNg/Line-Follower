void bt_control(int speedL_bt,int speedR_bt){
  char get_char_ = ' ';
 
  do{
    if(bt.available()>0){
      get_char_ = bt.read();
      if(diagnose_bt==true){
        Serial.println("--------------------------------------------------");
        Serial.println("bluetooth = "+ String(get_char_));
        Serial.println("--------------------------------------------------");
      }
      switch(get_char_){
        case 'F': Breverse(speedL_bt, speedR_bt);
        break;
        case 'R': Bforward(speedL_bt, speedR_bt);
        break;
//        case ' ': forward(0, speedR_bt);
//        break;
//        case '  ': forward(speedL_bt, 0);
//        break;
        case 'L': Bturn_right(speedL_bt, speedR_bt,0);
        break;
        case 'K': Bturn_left(speedL_bt, speedR_bt,0);
        break;
        default: Stop();
        break;
      }
      delay(0);  
    }
  }
  while(get_char_!='A');
}

