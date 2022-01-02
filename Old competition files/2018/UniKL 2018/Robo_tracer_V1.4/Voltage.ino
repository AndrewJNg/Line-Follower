int led_interval = 500;
long pastblink  = 0;
void voltage_check()
{
  int sensorValue = analogRead(V); //read the A0 pin value
  float voltage = sensorValue * (5.00 / 1023.00) * 2; //convert the value to a true voltage.
  
  if(diagnose_voltage == true){
    Serial.println("--------------------------------------------------");

  Serial.print("voltage = ");
  Serial.print(voltage);
  Serial.println(" V");
    
    Serial.println("--------------------------------------------------");
  } 
  
  if (voltage < 8 && (millis() - pastblink) > led_interval) //set the voltage considered low battery here
  {
    digitalWrite(led, HIGH);
     pastblink = millis();
  }
  else if (voltage > 8|| (millis() - pastblink) > (led_interval/3)){
    digitalWrite(led, LOW);
  }
 
}
