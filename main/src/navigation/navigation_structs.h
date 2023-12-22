#ifndef NAVIGATION_STRUCTS_H
#define NAVIGATION_STRUCTS_H

/*
NAVIGATION STATE STATE MACHINE.....
The navigation state machine is coded with an enum. The states are:
    1. NAV_IDLE: Nothing is performed. 
    2. NAV_RESET: The estimations are set to the default values, 
                  after one iteration the state is set to NAV_IDLE.
    3. NAV_INITIALIZATION: The state is initialized usign position data, 
                           magnetormeter and accelerometer.  
    4. NAV_STATIC_TUNING: The kalman filter engages and performs static alignment.
                          The static information is used to add virtual measuerements.
    5. NAV_DYNAMIC_TUNING: The dynamic tunig is a phase where high energy is provided 
                           system with minimal external disturbance(vibration etc). 
                           This is used to tune out the augmented state.
    6. NAV_NOMINAL: The kalman filter removes the tuned errors from the system and operates
                    only on the system states and IMU biases.
    8. NAV_AUGMENTED_NOMINAL: The kalman filter performs estimation on the system state and 
                              augmented vector. The implementation is similar to the 
                              NAV_DYNAMIC_TUNING but it includes disturbance rejection.
*/
enum NAVIGATION_STATE{
    NAV_IDLE,
    NAV_RESET,
    NAV_INITIALIZATION,
    NAV_STATIC_TUNING,
    NAV_DYNAMIC_TUNING, // implement when 9 DOF is available
    NAV_NOMINAL,
    NAV_AUGMENTED_NOMINAL,
};

/*
AUGMENTED STATE ESTIMATION.....
*/
struct AugmentedState{
    double accelerometer_bias[3];
    double gyroscope_bias[3];
    double accelerometer_misalignmet[3];
    double gyroscope_misalignment[3];
    double magnetometer_bias[3];
};

/*
NAVIGATION STATE ESTIMATION IN NED...
reference:
    https://en.wikipedia.org/wiki/Local_tangent_plane_coordinates
*/
struct NavigationEstimationNED{
    double position_ned[3];
    double velocity_ned[3];
    double quaternion_ned[4];
    AugmentedState AugmentedStateEstimation;
    // This can be improved only by taking diagonal+one of the two triangulars
    double covariance[15][15];
    double sampling_time;
};

/*
MAGNETOMETER MEASUREMENTS.....
*/
struct MagnetometerMeasurement
{
    double data[3];
    bool validity;
};

/*
GNSS MEASUREMENTS.....
*/
struct GnssMeasurement
{
    double position_ned[3];
    double velocity_ned[3];
    double covariance[6][6];
    unsigned long time_Stamp;
    bool validity;
};

struct Measuerements
{
    MagnetometerMeasurement MagnetometerMeas;
    GnssMeasurement GnssMeasurement;
};

#endif