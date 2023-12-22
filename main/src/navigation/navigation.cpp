#include "./navigation.h"
#include "./support_package/initialization.h"

initialization Initialization;

void navigation::step(NAVIGATION_STATE state, Measuerements* meas, ImuData* imuData, double heading){

    _current_state = state;
    switch (_current_state){
        case NAV_IDLE:
            break;
        case NAV_RESET:
            // We should change it to accept a structure
            Initialization.reset();
            Initialization.getState(&NavigationEstimation);
            break;
        case NAV_INITIALIZATION:
            // A magnetometer calibration procedure shall be modelled. 
            // See: https://www.sciencedirect.com/science/article/pii/S1474667016415983
            // The initialization shall be changed since the heading wont be available.
            // See: https://www.mdpi.com/1424-8220/21/6/2040
            Initialization.step(meas, imuData, heading);
            Initialization.getState(&NavigationEstimation);
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

void navigation::getState(NavigationEstimationNED* navState){
    *navState =  NavigationEstimation;
};
