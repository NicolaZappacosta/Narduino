#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "./navigation_structs.h"

class navigation{
private:
    double _position_ned[3];
    double _velocity_ned[3];
    double _quaternion_ned[4];
    double _accelerometer_bias[3]; 
    double _gyroscope_bias[3];
    double _magnetometer_bias[3]; // implement when 9 DOF is available
    double _accelerometer_misalignmet[3];
    double _covariance[12][12]; // find a way to extend it
    double _sampling_time;
    NAVIGATION_STATE _current_state = IDLE;
public:
    step(NAVIGATION_STATE state, double *acceleration, double *angular_rate, double *position, double *velocity, double *heading);
    resetInitialState(double *position, double *velocity, double *quaternion, double *covariance);
    getState(double *estimated_position, double *estimated_velocity, double *estimated_quaternion);
};

#endif