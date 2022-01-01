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


boolean bModeState = false;
boolean bStartState = false;

boolean bModeReading = false;
boolean bStartReading = false;

boolean LastbModeState = false;
boolean LastbStartState = false;

unsigned long bModelastDebounceTime = 50;
unsigned long bStartlastDebounceTime = 50;

unsigned long debounceDelay = 50;

void Button() {
  bModeReading = digitalRead(bMode);
  bStartReading = digitalRead(bStart);


  if (bModeReading != LastbModeState) {
    bModelastDebounceTime = millis();
  }

  if ((millis() - bModelastDebounceTime) > debounceDelay) {

    if (bModeReading != bModeState) {
      bModeState = bModeReading;

      if (bModeState == HIGH) {
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
  LastbModeState = bModeReading;



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
