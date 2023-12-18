#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

class initialization{
private:

    // To be changed
    void _compute_inclination(double *roll, double *pitch);
    void _compute_avg(double *acceleration);
    // We cannot use the gyro since it is bad quality
    int _accomulated_samples;
    double _avg_acceleration[3];
    double _position[3];
    double _velocity[3];
    double _quaternion[4];

public:
    initialization();
    void reset(double *position, double *velocity, double *acceleration);
    void step(double *position, double *velocity, double *acceleration, double *heading);
    void euler2quaternion(double roll, double pitch, double yaw);
    void getState(double *position, double *velocity, double* quaternion);
};

#endif