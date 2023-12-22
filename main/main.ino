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

Adafruit_MPU6050 mpu;
flight_computer fc;
unsigned long time_0;
unsigned long time_1;

void setup() {
  /*
  ImuSettings settings;
  // Setting the Serial port
  Serial.begin(115200);
  // Debug print
  Serial.println("Ciao-0");
  delay(1000);
  Serial.println("Ciao-1");
  delay(1000);
  // Setting the MPU6050
  settings.ACCELEROMETERS_RANGE = 8;
  settings.GYROSCPOPES_RANGE = 500;
  Serial.println("Ciao-2");
  delay(1000);
  // FC set IMU configs
  fc.setImu(&settings);
  delay(1000);
  // Debug print
  delay(1000);
  Serial.println("Fine settings");
  delay(1000);
  */
  {
  Serial.begin(115200);
  Serial.println("Initialize MPU6050");
  while (!mpu.begin(MPU6050_RANGE_2_G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(1000);
  }
}
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
  print_state_machine(&StateMachine);

  delay(1000-(time_1-time_0) );
};

void print_state_machine(STATE_MACHINE* StateMachine){
  /*
  // Separator
  Serial.println("----------------------------------------------");
  Serial.print("FC STATE: ");
  Serial.println(StateMachine->FcState);
  Serial.print("NAV STATE: ");
  Serial.println(StateMachine->NavState);
  Serial.println("----------------------------------------------");
  return;
  */
}
