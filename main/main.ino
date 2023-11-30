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
  // Setting the Baud rate
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  fc.setImu(MPU6050_RANGE_8_G, MPU6050_RANGE_500_DEG);
  delay(10);
}


void loop() {
  /* Get new sensor events with the readings */
  double a[3] = {0,0,0}; 
  double g[3] = {0,0,0};
  float temp = 0;

  fc.step();
  fc.getImuData(a, g, &temp);

  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a[0]);
  Serial.print(", Y: ");
  Serial.print(a[1]);
  Serial.print(", Z: ");
  Serial.print(a[2]);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g[0]);
  Serial.print(", Y: ");
  Serial.print(g[1]);
  Serial.print(", Z: ");
  Serial.print(g[2]);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" degC");

  Serial.println("");
  delay(500);
}
