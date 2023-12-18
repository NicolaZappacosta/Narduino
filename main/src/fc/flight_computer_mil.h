#ifndef FLIGHT_COMPUTER_MIL_H
#define FLIGHT_COMPUTER_MIL_H

#include "../imu/imu_driver.h"
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include "../navigation/navigation.h"

enum FC_STATE{
    FC_IDLE,
    FC_RESET,
    FC_INITIALIZATION,
    FC_STATIC_TUNING,
    FC_DYNAMIC_TUNING, // implement when 9 DOF is available
    FC_NOMINAL,
    FC_AUGMENTED_NOMINAL,
};

class flight_computer{
private:
    imu_driver imu;
    navigation nav;
    FC_STATE _current_state = FC_IDLE;
public:
    step();
    void getImuData(double *acceleration, double *angular_rate, float *temperature);
    void setImu(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting);
    void setFC(int Baud_rate);
    void runNavigation();
    NAVIGATION_STATE map2NavigationState(NAVIGATION_STATE _navigation_state);
    void getState(FC_STATE *fc_state);
    void getCmd();
    void getNavigationState(double *estimated_position, double *estimated_velocity, double *estimated_quaternion);
    void print2Serial();
};  

#endif