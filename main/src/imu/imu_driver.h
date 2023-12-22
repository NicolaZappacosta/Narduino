#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "./imu_structs.h"
#include <Wire.h>
#include <Arduino.h>

class imu_driver{
private:
    /*
    Attributes:
        - ImuData: it is a struct which stores the information of the imu.
        - mpu: it is the class in charge of reading the MPU data. 
    */
    ImuData data;
    Adafruit_MPU6050 mpu;
    /*
    Methods:
        - _set_accelerometers(): method in charge of setting the accelerometers 
            informtaion.
        - _set_gyroscopes(): method in charge of setting the gyroscopes
    */
    void _set_accelerometers(ImuSettings* settings);
    void _set_gyroscopes(ImuSettings* settings);

public:
    void set_imu_driver(ImuSettings* settings);
    void get(ImuData* dataOut);
    void step();
};

#endif