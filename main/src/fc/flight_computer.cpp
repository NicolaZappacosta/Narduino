#include "./flight_computer.h"

flight_computer::step(){
    imu.step();
};
void flight_computer::getImuData(double *acceleration, double *angular_rate, float *temperature){
    imu.get(acceleration, angular_rate, temperature);
    return;
};
void flight_computer::setImu(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting){
    imu.set_imu_driver(accel_setting, gyro_setting);
};
