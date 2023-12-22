#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include "../navigation_structs.h"
#include "../../imu/imu_structs.h"

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
    void reset();
    void step(Measuerements* Meas, ImuData* ImuData, double heading);
    void euler2quaternion(double roll, double pitch, double yaw);
    void getState(NavigationEstimationNED* NavigationEstimation);
};

#endif