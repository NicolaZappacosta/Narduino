#include "./flight_computer.h"

flight_computer::step(){
    imu.step();
    getCmd();
    runNavigation();
};
void flight_computer::getImuData(double *acceleration, double *angular_rate, float *temperature){
    imu.get(acceleration, angular_rate, temperature);
    return;
};
void flight_computer::setImu(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting){
    imu.set_imu_driver(accel_setting, gyro_setting);
};

void flight_computer::runNavigation(){
    
    double acceleration_meas[3];
    double angular_rate_meas[3];
    /*Hardcoded for now from the phone data singe the 9-DOF sensor in not available
    You should implement a GNSS driver for this.
    */
    double position_meas[3] = {48.359733, 10.871368, 507};
    double velocity_meas[3] = {0, 0, 0};
    double heading_meas = 3.14159265;
    float temperature_meas;
    NAVIGATION_STATE _navigation_state; // This can be centralized in struct()
    _navigation_state = map2NavigationState(_navigation_state);

    imu.get(acceleration_meas, angular_rate_meas, &temperature_meas);
    nav.step(_navigation_state, acceleration_meas, angular_rate_meas, position_meas, velocity_meas, &heading_meas);
};

NAVIGATION_STATE flight_computer::map2NavigationState(NAVIGATION_STATE _navigation_state){
    Serial.println("Let's go");
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

void flight_computer::getState(FC_STATE *fc_state){
    *fc_state = _current_state;
};

void flight_computer::setFC(int Baud_rate){
};

void flight_computer::getCmd(){
    // This should be a class...
    const int MAX_STRING_LENGTH = 12; // To define the right place for this
    static char message[MAX_STRING_LENGTH];
    static int message_position = 0;
    
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
            Serial.println("");
            Serial.print("mode to select: ");
            Serial.print(mode);
            Serial.println("");
            // Here you should develope a mode manager

            switch (mode) {
                case 0:
                    _current_state = FC_IDLE;
                    break;
                case 1:
                    _current_state = FC_RESET;
                    break;
                case 2:
                    _current_state = FC_INITIALIZATION;
                    break;
                case 3:
                    _current_state =  FC_STATIC_TUNING;
                    break;
                case 4: // implement when 9 DOF is available
                    _current_state = FC_DYNAMIC_TUNING;
                    break;
                case 5:
                    _current_state = FC_NOMINAL;
                    break;
                case 6:
                    _current_state = FC_AUGMENTED_NOMINAL;
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

void flight_computer::print2Serial(){

    double a[3];
    double g[3];
    float temp;
    
    getImuData(a, g, &temp);

    /* Print out the values */
    Serial.print("FC STATE = ");
    switch (_current_state) {
        case FC_IDLE:
            Serial.println("IDLE");
            break;
        case FC_RESET:
            Serial.println("RESET");
            break;
        case FC_INITIALIZATION:
            Serial.println("INITIALIZATION");
            break;
        case FC_STATIC_TUNING:
            Serial.println("STATIC_TUNING");
            break;
        case FC_DYNAMIC_TUNING: // implement when 9 DOF is available
            Serial.println("DYNAMIC_TUNING");
            break;
        case FC_NOMINAL:
            Serial.println("NOMINAL");
            break;
        case FC_AUGMENTED_NOMINAL:
            Serial.println("AUGMENTED_NOMINAL");
            break;
        default:
            Serial.println("Unknown state");
    };

    NAVIGATION_STATE _navigation_state; // This can be centralized in struct()
    _navigation_state = map2NavigationState(_navigation_state);

    Serial.print("NAV STATE = ");
    switch (_navigation_state) {
        case IDLE:
            Serial.println("IDLE");
            break;
        case RESET:
            Serial.println("RESET");
            break;
        case INITIALIZATION:
            Serial.println("INITIALIZATION");
            break;
        case STATIC_TUNING:
            Serial.println("STATIC_TUNING");
            break;
        case DYNAMIC_TUNING: // implement when 9 DOF is available
            Serial.println("DYNAMIC_TUNING");
            break;
        case NOMINAL:
            Serial.println("NOMINAL");
            break;
        case AUGMENTED_NOMINAL:
            Serial.println("AUGMENTED_NOMINAL");
            break;
        default:
            Serial.println("Unknown state");
    };

    /*
    //Serial.print(*fc_state);
    Serial.println("-------------------------------------");
    Serial.print("Acceleration X: ");
    Serial.print(a[0]);
    Serial.print(", Y: ");
    Serial.print(a[1]);
    Serial.print(", Z: ");
    Serial.print(a[2]);
    Serial.println(" m/s^2");

    Serial.print("Rotation X: ");
    Serial.print(g[0]);
    Serial.print(", Y: ");
    Serial.print(g[1]);
    Serial.print(", Z: ");
    Serial.print(g[2]);
    Serial.println(" rad/s");

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" degC");

    Serial.println("");
    */
    /**/
    //Get navigation estimated state
    double estimated_position[3];
    double estimated_velocity[3];
    double estimated_quaternion[4];
    

    getNavigationState(estimated_position, estimated_velocity, estimated_quaternion);

    Serial.println("Navigation state ----------------------------");
    Serial.print("Quaternion: q_0 =");
    Serial.print(estimated_quaternion[0]);
    Serial.print(", q_1 =");
    Serial.print(estimated_quaternion[1]);
    Serial.print(", q_2 =");
    Serial.print(estimated_quaternion[2]);
    Serial.print(", q_3 = ");
    Serial.print(estimated_quaternion[3]);
    
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
