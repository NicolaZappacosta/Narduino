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
#include "./src/fc/flight_computer_structs.h"

flight_computer fc;
unsigned long time_0;
unsigned long time_1;

void setup(void) {
  ImuSettings settings;
  // Setting the Serial port
  Serial.begin(115200);
  // Debug print
  Serial.println("Inizio");
  // Setting the MPU6050
  settings.ACCELEROMETERS_RANGE = 8;
  settings.GYROSCPOPES_RANGE = 500;
  // FC set IMU configs
  fc.setImu(&settings);
  // Debug print
  delay(1000);
  Serial.println("Fine settings");
  delay(1000);
}

void loop() {
  STATE_MACHINE StateMachine;
  Serial.println("Sto in loop() --------------------------------");
  time_0 = millis();
  fc.getCmd();
  fc.step();
  fc.get_state_machine(&StateMachine);
  time_1 = millis();
  // Print process time
  Serial.print("FC step time: ");
  Serial.print((time_1-time_0));
  Serial.println(" msec;");
  // Separator
  Serial.println("----------------------------------------------");
  Serial.print("FC STATE: ");
  Serial.println(StateMachine.FcState);
  Serial.print("NAV STATE: ");
  Serial.println(StateMachine.NavState);
  Serial.println("----------------------------------------------");
  delay(1000-(time_1-time_0) );
}
