#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "./navigation_structs.h"
#include "../imu/imu_structs.h"

class navigation{
private:
    //Attributes
    NavigationEstimationNED NavigationEstimation;
    NAVIGATION_STATE _current_state = NAV_IDLE;
    
public:
    void step(NAVIGATION_STATE state, Measuerements* meas, ImuData* imuData, double heading);
    void getState(NavigationEstimationNED* navState);
};

#endif