//User Interface

unsigned long buzzerMillis = 0;
int buzzerCurrentCount = 0;
int totalBuzz = 0;
boolean buzzerState = false;
int buzzInterval = 100;

void Buzzer() {
  if ((currentMillis - buzzerMillis >= buzzInterval) && (buzzerCurrentCount < totalBuzz)) {
    buzzerMillis = currentMillis;

    if (buzzerState == LOW) {
      buzzerState = HIGH;

    } else if (buzzerState == HIGH) {
      buzzerState = LOW;
      buzzerCurrentCount++;
    }
    // Serial.println(buzzerState);
    digitalWrite(buzzer, buzzerState);
  }
  else if (buzzerCurrentCount > totalBuzz) {
    buzzerState = LOW;
    buzzInterval = 100;
  }
}


void Buzz( int beeps, int beepsInterval) {
  buzzerCurrentCount = 0;
  totalBuzz = beeps;
  buzzInterval = beepsInterval;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


boolean bAddState = false;
boolean bMinusState = false;
boolean bStartState = false;

boolean bAddReading = false;
boolean bMinusReading = false;
boolean bStartReading = false;

boolean LastbAddState = false;
boolean LastbMinusState = false;
boolean LastbStartState = false;

unsigned long bAddlastDebounceTime = 50;
unsigned long bMinuslastDebounceTime = 50;
unsigned long bStartlastDebounceTime = 50;

unsigned long debounceDelay = 50;

void Button() {
  bAddReading = digitalRead(bAdd);
  bMinusReading = digitalRead(bMinus);
  bStartReading = digitalRead(bStart);


  if (bAddReading != LastbAddState) {
    bAddlastDebounceTime = millis();
  }

  if ((millis() - bAddlastDebounceTime) > debounceDelay) {

    if (bAddReading != bAddState) {
      bAddState = bAddReading;

      if (bAddState == HIGH) {
        Mode++;
        if (Mode > 4) {
          Mode = 1;
        }
        else if (Mode < 1) {
          Mode = 1;
        }
        Start = false;
        Buzz(Mode, 100);
      }
    }
  }
  LastbAddState = bAddReading;



  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (bMinusReading != LastbMinusState) {
    bMinuslastDebounceTime = millis();
  }

  if ((millis() - bMinuslastDebounceTime) > debounceDelay) {

    if (bMinusReading != bMinusState) {
      bMinusState = bMinusReading;

      if (bMinusState == HIGH) {
        Mode--;
        if (Mode > 4) {
          Mode = 4;
        }
        else if (Mode < 1) {
          Mode = 1;
        }
        Start = false;
        Buzz(Mode, 100);
      }
    }
  }
  LastbMinusState = bMinusReading;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if (bStartReading != LastbStartState) {
    bStartlastDebounceTime = millis();
  }

  if ((millis() - bStartlastDebounceTime) > debounceDelay) {

    if (bStartReading != bStartState) {
      bStartState = bStartReading;

      // only toggle the LED if the new button state is HIGH
      if (bStartState == HIGH) {
        Start = !Start;
        Buzz(1, 50);

      }
    }
  }
  LastbStartState = bStartReading;
  //Serial.println(Mode);
}
