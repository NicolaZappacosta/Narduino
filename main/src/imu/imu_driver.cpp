#include "./imu_driver.h"

imu_driver::set_imu_driver(mpu6050_accel_range_t accel_setting, mpu6050_gyro_range_t gyro_setting){
    // Try to initialize!
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(accel_setting);
  mpu.setGyroRange(gyro_setting);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
};
imu_driver::step(){
  mpu.getEvent(&_accelerometer, &_gyroscope, &_temperature);
}
void imu_driver::get(double *acceleration, double *angular_rate ,float *temperature){
  acceleration[0] = _accelerometer.acceleration.x;
  acceleration[1] = _accelerometer.acceleration.y;
  acceleration[2] = _accelerometer.acceleration.z;
  angular_rate[0] = _gyroscope.gyro.x;
  angular_rate[1] = _gyroscope.gyro.y;
  angular_rate[2] = _gyroscope.gyro.z;
  *temperature = _temperature.temperature;
  return;
};
