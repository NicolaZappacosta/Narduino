#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

#include "../imu/imu_driver.h"
#include <Adafruit_Sensor.h>

class flight_computer{
private:
    imu_driver imu;
public:
    step();
    void getImuData(double *acceleration, double *angular_rate, float *temperature);
    void setImu(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting);
};

#endif