#ifndef FLIGHT_COMPUTER_H
#define FLIGHT_COMPUTER_H

// ARDUINO LIBRARIES - TRY TO REMOVE THEM
#include <Adafruit_Sensor.h>
#include <Arduino.h>

// NARDUINO LIBRARIES 
#include "../navigation/navigation.h"
#include "../imu/imu_driver.h"
#include "../imu/imu_structs.h"
#include "./flight_computer_structs.h"
#include "../navigation/navigation_structs.h"

class flight_computer{
private:
    imu_driver imu;
    navigation nav;
    STATE_MACHINE _state_machine_state;
public:
    flight_computer();
    step();
    void get_state_machine(STATE_MACHINE* StateMachine);
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