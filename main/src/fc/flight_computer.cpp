#include "./flight_computer.h"


void flight_computer::get_state_machine(STATE_MACHINE* StateMachine){
    *StateMachine = _state_machine_state;
};
flight_computer::flight_computer(){
    _state_machine_state.FcState = FC_IDLE;
    _state_machine_state.NavState = NAV_IDLE;
}
flight_computer::step(){
    /*
    Basic assumption is that the FC processes are synchronous. 
    */
    imu.step();
    getCmd();
    runNavigation();
};
void flight_computer::getImuData(ImuData* data){
    imu.get(data);
    return;
};
void flight_computer::setImu(ImuSettings* settings){
    imu.set_imu_driver(settings);
};

void flight_computer::runNavigation(){
    
    ImuData data;
    /*Hardcoded for now from the phone data since the 9-DOF sensor in not available
    You should implement a GNSS driver for this.
    */
    double position_meas[3] = {48.359733, 10.871368, 507};
    double velocity_meas[3] = {0, 0, 0};
    double heading_meas = 3.14159265;
    float temperature_meas;
    NAVIGATION_STATE _navigation_state; // This can be centralized in struct()
    _navigation_state = _state_machine_state.NavState;

    getImuData(&data);

    // Interface layer - remove whenever possible
    double acceleration_meas[3];
    double angular_rate_meas[3];
    for(int i; i<3; i++){
        acceleration_meas[i] = data.acceleration[i];
        angular_rate_meas[i] = data.angularRate[i];
    }

    nav.step(_navigation_state, acceleration_meas, angular_rate_meas, position_meas, velocity_meas, &heading_meas);
};
/*
NAVIGATION_STATE flight_computer::map2NavigationState(NAVIGATION_STATE _navigation_state){
    switch (_current_state){
        case FC_IDLE:
            _navigation_state = IDLE;
            break;
        case FC_RESET:
            _navigation_state = RESET;
            break;
        case FC_INITIALIZATION:
            _navigation_state = INITIALIZATION;
            break;
        case FC_STATIC_TUNING:
            _navigation_state = STATIC_TUNING;
            break;
        case FC_DYNAMIC_TUNING: // implement when 9 DOF is available
            _navigation_state = DYNAMIC_TUNING;
            break;
        case FC_NOMINAL:
            _navigation_state = NOMINAL;
            break;    
        case FC_AUGMENTED_NOMINAL:
            _navigation_state = AUGMENTED_NOMINAL;
            break;
        default:
            Serial.println("I shouldn't be here");
    };
    return _navigation_state;
};
*/
void flight_computer::getState(FC_STATE *fc_state){
    *fc_state = _state_machine_state.FcState;
};

void flight_computer::setFC(int Baud_rate){
};

void flight_computer::getCmd(){
    // This should be a class...
    const int MAX_STRING_LENGTH = 12; // To define the right place for this
    static char message[MAX_STRING_LENGTH];
    static int message_position = 0;
    // The command should be generalized and handled by a telemetry interface
    while (Serial.available()>0 && message_position<MAX_STRING_LENGTH-1){
        char inByte = Serial.read();
        Serial.println(inByte);
        if (inByte != '\n'){
            message[message_position] = inByte;
            message_position++;
        }
        else{
            // This special char is required for the atoi function()
            message[message_position] = "\0";
            int mode = atoi(message);
            /*
            Here you should develope a mode manager...
            Currently the state machine of the Navigation is one-to-one with the FC one.
            A more complex logic can be impelmented.
            */ 

            switch (mode) {
                case 0:
                    _state_machine_state.FcState = FC_IDLE;
                    _state_machine_state.NavState = NAV_IDLE;
                    break;
                case 1:
                    _state_machine_state.FcState = FC_RESET;
                    _state_machine_state.NavState = NAV_RESET;
                    break;
                case 2:
                    _state_machine_state.FcState = FC_INITIALIZATION;
                    _state_machine_state.NavState = NAV_INITIALIZATION;
                    break;
                case 3:
                    _state_machine_state.FcState = FC_STATIC_TUNING;
                    _state_machine_state.NavState = NAV_STATIC_TUNING;
                    break;
                case 4: // implement when 9 DOF is available
                    _state_machine_state.FcState = FC_DYNAMIC_TUNING;
                    _state_machine_state.NavState = NAV_DYNAMIC_TUNING;
                    break;
                case 5:
                    _state_machine_state.FcState = FC_NOMINAL;
                    _state_machine_state.NavState = NAV_NOMINAL;
                    break;
                case 6:
                    _state_machine_state.FcState = FC_AUGMENTED_NOMINAL;
                    _state_machine_state.NavState = NAV_AUGMENTED_NOMINAL;
                    break;
                default:
                    Serial.println("Unknown state");
            };
            message_position = 0;
            for(int i = 0; i<MAX_STRING_LENGTH; i++){
                message[i] = "\0";
            };
        }
    }
};

void flight_computer::getNavigationState(double *estimated_position, double *estimated_velocity, double *estimated_quaternion){
    double _position_ned[3];
    double _velocity_ned[3];
    double _quaternion_ned[4];

    nav.getState(_position_ned, _velocity_ned, _quaternion_ned);

    for(int i=0;i<3;i++){
        estimated_position[i] = _position_ned[i];
        estimated_velocity[i] = _velocity_ned[i];
    };
    for(int i=0;i<4;i++){
        estimated_quaternion[i] = _quaternion_ned[i];
    };
};
