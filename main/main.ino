// Main script to read the IMU for the moment
/*
This script will work as the flight computer and will be implementing
executing the classes for the flight computer etc
*/
// Importing headers
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "./src/fc/flight_computer.h"

flight_computer fc;

void setup(void) {
  Serial.begin(115200);
  Serial.print("ciao");
  fc.setImu(MPU6050_RANGE_8_G, MPU6050_RANGE_500_DEG);
  Serial.print("Ciao");
  delay(10);
}

void loop() {
  Serial.print("Ciao");
  fc.step();
  fc.print2Serial();
  delay(1000);
}
