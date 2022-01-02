
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 gyro(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
 gyro.begin();
 gyro.calcGyroOffsets();
}

void loop() {
  gyro.update();
  Serial.print("angleX : ");
  Serial.print(gyro.getAngleX());
  Serial.print("\tangleY : ");
  Serial.print(gyro.getAngleY());
  Serial.print("\tangleZ : ");
  Serial.println(gyro.getAngleZ());
}
