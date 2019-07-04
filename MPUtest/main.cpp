//          Copyright Youri de Vor 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "hwlib.hpp"
#include "MPU6050.hpp"

int main(){

  // Setting up the pins and creating an MPU6050 object
  auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
  auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
  auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
  auto mpu = Mpu6050(bus, 0x68);
  hwlib::wait_ms( 500 );

  // Set all the defaults and disable sleepmode so it's able to measure
  mpu.disableSleep();
  mpu.setGyroConfig(0);
  mpu.setAcceleroConfig(0);
  mpu.setConfig(0);

  uint8_t passedTests = 0;

  // Do all the measurements
  int16_t AccX = mpu.readAccX();
  int16_t AccY = mpu.readAccY();
  int16_t AccZ = mpu.readAccZ();

  int16_t GyroX = mpu.readGyroX();
  int16_t GyroY = mpu.readGyroY();
  int16_t GyroZ = mpu.readGyroZ();

  int16_t temperature = mpu.readTemperature();

  hwlib::wait_ms(500);

  // Is it connected? Is the content of the WHO_AM_I register what we expect?
  if(mpu.readRegister(0x75) == 0x68){
    hwlib::cout << "MPU6050 successfully connected" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "MPU6050 not connected properly" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  // Testing if the registers can be successfully configured (and read)
  mpu.setConfig(0);
  if( mpu.readConfig() == 0){
    hwlib::cout << "CONFIG write/read test passed for value 0" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "CONFIG write/read test failed for value 0" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setConfig(3);
  if( mpu.readConfig() == 3){
    hwlib::cout << "CONFIG write/read test passed for value 3" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "CONFIG write/read test failed for value 3" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setConfig(6);
  if( mpu.readConfig() == 6){
    hwlib::cout << "CONFIG write/read test passed for value 6" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "CONFIG write/read test failed for value 6" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setAcceleroConfig(0);
  if( mpu.readAcceleroConfig() == 16384){
    hwlib::cout << "ACCEL_CONFIG write/read test passed for value 0" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "ACCEL_CONFIG write/read test failed for value 0" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setAcceleroConfig(1);
  if( mpu.readAcceleroConfig() == 8192){
    hwlib::cout << "ACCEL_CONFIG write/read test passed for value 1" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "ACCEL_CONFIG write/read test failed for value 1" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setAcceleroConfig(2);
  if( mpu.readAcceleroConfig() == 4096){
    hwlib::cout << "ACCEL_CONFIG write/read test passed for value 2" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "ACCEL_CONFIG write/read test failed for value 2" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setAcceleroConfig(3);
  if( mpu.readAcceleroConfig() == 2048){
    hwlib::cout << "ACCEL_CONFIG write/read test passed for value 3" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "ACCEL_CONFIG write/read test failed for value 3" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setGyroConfig(0);
  if( mpu.readGyroConfig() <= 131.1 && mpu.readGyroConfig() >= 130.9){
    hwlib::cout << "GYRO_CONFIG write/read test passed for value 0" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "GYRO_CONFIG write/read test failed for value 0" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setGyroConfig(1);
  if( mpu.readGyroConfig() <= 65.6 && mpu.readGyroConfig() >= 65.4){
    hwlib::cout << "GYRO_CONFIG write/read test passed for value 1" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "GYRO_CONFIG write/read test failed for value 1" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setGyroConfig(2);
  if( mpu.readGyroConfig() <= 32.9 && mpu.readGyroConfig() >= 32.7){
    hwlib::cout << "GYRO_CONFIG write/read test passed for value 2" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "GYRO_CONFIG write/read test failed for value 2" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  mpu.setGyroConfig(3);
  if( mpu.readGyroConfig() <= 16.5 && mpu.readGyroConfig() >= 16.3){
    hwlib::cout << "GYRO_CONFIG write/read test passed for value 3" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "GYRO_CONFIG write/read test failed for value 3" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  // Testing if sleep can be enabled and disabled
  mpu.enableSleep();
  if( mpu.readRegister(0x6B) == 1){
    hwlib::cout << "Sleep mode succesfully activated" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Failed to activate sleepmode" << hwlib::endl;
  }

  mpu.disableSleep();
  if( mpu.readRegister(0x6B) == 0){
    hwlib::cout << "Sleep mode succesfully deactivated" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Failed to deactivate sleepmode" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  // Testing if the measured values are realistic
  if( AccX >= -981 && AccX <= 981){
    hwlib::cout << "Accelerometer X axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Accelerometer X axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if( AccY >= -981 && AccY <= 981){
    hwlib::cout << "Accelerometer Y axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Accelerometer Y axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if( AccZ >= -981 && AccZ <= 981){
    hwlib::cout << "Accelerometer Z axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Accelerometer Z axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);
  mpu.setGyroConfig(0);

  if( GyroX >= -125 && GyroX <= 125){
    hwlib::cout << "Gyroscope X axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Gyroscope X axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if( GyroY >= -125 && GyroY <= 125){
    hwlib::cout << "Gyroscope Y axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Gyroscope Y axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if( GyroZ >= -125 && GyroZ <= 125){
    hwlib::cout << "Gyroscope Z axis passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Gyroscope Z axis failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if( temperature >= -30 && temperature <= 30){
    hwlib::cout << "Temperature sensor passed" << hwlib::endl;
    passedTests++;
  }else{
    hwlib::cout << "Temerature sensor failed" << hwlib::endl;
  }

  hwlib::wait_ms(500);

  if (passedTests == 21){
    hwlib::cout << "All MPU6050 tests passed!" << hwlib::endl;
  }

}
