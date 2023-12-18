#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

// ARDUINO LIBRARIES - TRY TO REMOVE THEM
#include <Adafruit_Sensor.h>
#include <Arduino.h>

// NARDUINO LIBRARIES 
#include "../navigation/navigation.h"
#include "../imu/imu_driver.h"
#include "../imu/imu_structs.h"


// THIS SHOULDN'T BE HERE
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
    void getImuData(ImuData* data);
    void setImu(ImuSettings* settings);
    void setFC(int Baud_rate);
    void runNavigation();
    NAVIGATION_STATE map2NavigationState(NAVIGATION_STATE _navigation_state);
    void getState(FC_STATE *fc_state);
    void getCmd();
    void getNavigationState(double *estimated_position, double *estimated_velocity, double *estimated_quaternion);
};  

#endif