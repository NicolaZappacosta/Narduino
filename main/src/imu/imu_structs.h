#ifndef IMU_STRUCTS_H
#define IMU_STRUCTS_H

struct ImuSettings{
    /*
    This struct() is used to pass settings to the IMU drivers independently from the driver implementation.
    This allows more flexibility in the selection of the driver.
    */
    
    // Accelerometer range specified in Gs and given as an integer, 
    int ACCELEROMETERS_RANGE;
    // Gyroscope range specified in DEGs and given as an integer,
    int GYROSCPOPES_RANGE;
    // More inputs data exists check the settings of the ADAFRUIT 6050 or similar
};

struct ImuData{
    /*
    This struct stores the data of the IMU and it can be extended. It is meant to be flexible to be used 
    by different sensors.
    */
    double acceleration[3];
    double angularRate[3];
    float temperature;
};


#endif