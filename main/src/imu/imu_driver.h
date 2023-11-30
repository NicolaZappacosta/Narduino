#ifndef IMU_DRIVER_H
#define IMU_DRIVER_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class imu_driver{
private:
    sensors_event_t _accelerometer;
    sensors_event_t _gyroscope;
    sensors_event_t _temperature;
    double acceleration;
    double angular_rate;
    float temperature;
    Adafruit_MPU6050 mpu;
public:
    set_imu_driver(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting);
    void get(double *acceleration, double *angular_rate,float *temperature);
    step();
};

#endif