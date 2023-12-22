#include "./initialization.h"
#include <math.h>

initialization::initialization(){
    // The constructor sets everything to zero.
    for(int i = 0; i<3; i++){
        _avg_acceleration[i] = 0;
        _position[i] = 0;
        _velocity[i] = 0; 
    };
    _accomulated_samples = 0;
};
void initialization::_compute_inclination(double *roll, double *pitch){
    //TODO
    return;
};

void initialization::_compute_avg(double *acceleration){
    for(int i = 0; i<3; i++){
        _avg_acceleration[i] = _avg_acceleration[i]*_accomulated_samples/(_accomulated_samples+1)+acceleration[i]/_accomulated_samples; 
        // We should compute the avg position too and the data shall be in a struct.
    };
    _accomulated_samples++;
    return;
};

void initialization::reset(){
    for(int i = 0; i<3; i++){
        _avg_acceleration[i] = 0;
        _position[i] = 0;
        _velocity[i] = 0; 
    };
    for(int i = 0; i<4; i++){
        _quaternion[i] = 0; 
    };
    _accomulated_samples = 0;
    return;
};

void initialization::step(Measuerements* Meas, ImuData* ImuData, double heading){
    
    double roll;
    double pitch;
    double yaw;

    for(int i = 0; i<3; i++){
        _position[i] = Meas->GnssMeasurement.position_ned[i];
        _velocity[i] = Meas->GnssMeasurement.velocity_ned[i]; 
    };
    _compute_avg(ImuData->acceleration);
    /*
    Here the assumption is made where the vertical axis is the same as the MPU and it's
    the z-axis.
    */
    roll = _avg_acceleration[1]/_avg_acceleration[2];
    pitch = _avg_acceleration[0]/_avg_acceleration[2];
    yaw =  heading;

    euler2quaternion(roll, pitch, yaw);

    return;
};

void initialization::euler2quaternion(double roll, double pitch, double yaw){

    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    _quaternion[0] = cr * cp * cy + sr * sp * sy;
    _quaternion[1] = sr * cp * cy - cr * sp * sy;
    _quaternion[2] = cr * sp * cy + sr * cp * sy;
    _quaternion[3] = cr * cp * sy - sr * sp * cy;

};

void initialization::getState(NavigationEstimationNED* NavigationEstimation){
    for(int i = 0; i<3; i++){
        NavigationEstimation->position_ned[i] = _position[i];
        NavigationEstimation->velocity_ned[i] = _velocity[i]; 
    };
    for(int i = 0; i<4; i++){
       NavigationEstimation->quaternion_ned[i] = _quaternion[i]; 
    };
};

