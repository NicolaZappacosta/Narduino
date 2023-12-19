#include "./navigation.h"
#include "./support_package/initialization.h"
#include <Arduino.h>

initialization Initialization;

navigation::step(NAVIGATION_STATE state, double *acceleration, double *angular_rate, double *position, double *velocity, double *heading){
    _current_state = state;
    switch (_current_state){
        case NAV_IDLE:
            break;
        case NAV_RESET:
            // We should change it to accept a structure
            Initialization.reset(position, velocity, acceleration);
            Initialization.getState(_position_ned, _velocity_ned, _quaternion_ned);
            break;
        case NAV_INITIALIZATION:
            Initialization.step(position, velocity, acceleration, heading);
            Initialization.getState(_position_ned, _velocity_ned, _quaternion_ned);
            break;
        case NAV_STATIC_TUNING:
            // Do something
            break;
        case NAV_DYNAMIC_TUNING:
            // Do something
            break;
        case NAV_NOMINAL:
            // Do something
            break;
        case NAV_AUGMENTED_NOMINAL:
            // Do something 
            break;
    };
};

navigation::getState(double *estimated_position, double *estimated_velocity, double *estimated_quaternion){
    for(int i=0;i<3;i++){
        estimated_position[i] = _position_ned[i];
        estimated_velocity[i] = _velocity_ned[i];
    };
    for(int i=0;i<4;i++){
        estimated_quaternion[i] = _quaternion_ned[i];
    };
};
