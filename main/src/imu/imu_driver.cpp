#include "./imu_driver.h"

/*
PRIVATE METHODS ----------------------------------------------------------
*/
void imu_driver::_set_accelerometers(ImuSettings* settings){
  
  // The settings shall be extended 
  mpu6050_accel_range_t range_setting;
  // The switch case shall be extended
  switch (settings->ACCELEROMETERS_RANGE)
  {
  case 8:
    range_setting = MPU6050_RANGE_8_G;
    break;
  default:
    break;
  }
  mpu.setAccelerometerRange(range_setting);
  return;
}

void imu_driver::_set_gyroscopes(ImuSettings* settings){
  
  // The settings shall be extended 
  mpu6050_gyro_range_t range_setting;
  // The switch case shall be extended
  switch (settings->ACCELEROMETERS_RANGE)
  {
  case 500:
    range_setting = MPU6050_RANGE_500_DEG;
    break;
  default:
    break;
  }
  mpu.setGyroRange(range_setting);
  return;
}

/*
PUBLIC METHODS -----------------------------------------------------------
*/
void imu_driver::set_imu_driver(ImuSettings* settings){
    // Try to initialize!
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }

  _set_accelerometers(settings);
  _set_gyroscopes(settings);
  // Here a wrapper function shall be created
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  return;
};

void imu_driver::step(){
  /*
  This method reads the data from the MPU and spits out the updated
  struct ImuData.  
  */
  // Allocating local variables.
  sensors_event_t accelerometer;
  sensors_event_t gyroscope;
  sensors_event_t temperature;
  // MPU library
  mpu.getEvent(&accelerometer, &gyroscope, &temperature);
  // Assign to data struct()
  data.acceleration[0] = accelerometer.acceleration.x;
  data.acceleration[1] = accelerometer.acceleration.y;
  data.acceleration[2] = accelerometer.acceleration.z;
  data.angularRate[0] = gyroscope.gyro.x;
  data.angularRate[1] = gyroscope.gyro.y;
  data.angularRate[2] = gyroscope.gyro.z;
  data.temperature = temperature.temperature;
  return;

}
void imu_driver::get(ImuData* dataOut){
  *dataOut = data;
  return;
};
