int voltageTrigger = 7.0;
unsigned long ledMillis = 0;
int ledState = 0;

void VoltageChecker() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.00 / 1023.00) * 2;


  if (voltage < voltageTrigger) {
    if (currentMillis - ledMillis >= 2000) {
      ledMillis = currentMillis;
      if (ledState == LOW) {
        ledState = HIGH;

        // Buzz(2,80);

      } else {
        ledState = LOW;
      }
    }
  }
  else {
    ledState = HIGH;
  }
  digitalWrite(led, ledState);



  //Serial.println(voltage);
}
