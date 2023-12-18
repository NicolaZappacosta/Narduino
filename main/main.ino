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
#include "./src/imu/imu_structs.h"
flight_computer fc;

void setup(void) {
  ImuSettings settings;
  Serial.begin(115200);
  Serial.print("ciao");
  settings.ACCELEROMETERS_RANGE = 8;
  settings.GYROSCPOPES_RANGE = 500;
  fc.setImu(&settings);
  Serial.print("Ciao");
  delay(10);
}

void loop() {
  Serial.print("Ciao");
  fc.step();
  delay(1000);
}
