
//          Copyright Youri de Vor 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "MPU6050.hpp"
#include "hwlib.hpp"
#include <cmath>

Mpu6050::Mpu6050(hwlib::i2c_bus_bit_banged_scl_sda &sensor, const uint8_t &sensorAddress):
	sensor( sensor ),
	sensorAddress( sensorAddress )
{}

void Mpu6050::selectRegister(const uint8_t &registerAdress){
  hwlib::i2c_write_transaction(sensor, sensorAddress).write(registerAdress);
}

void Mpu6050::disableSleep(){
	const uint8_t sleepValue[2] = {PWR_MGMT_1, 0};
	hwlib::i2c_write_transaction(sensor, sensorAddress).write(sleepValue, 2);
}

void Mpu6050::enableSleep(){
	const uint8_t sleepValue[2] = {PWR_MGMT_1, 1};
	hwlib::i2c_write_transaction(sensor, sensorAddress).write(sleepValue, 2);
}

uint8_t Mpu6050::readRegister(const uint8_t &registerAdress){
	selectRegister(registerAdress);
	uint8_t value = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	return value;
}

int16_t Mpu6050::concatenateBytes(const uint8_t &msb, const uint8_t &lsb){
	int16_t value = 0;
	value = (msb << 8) | lsb;
	return value;
}

int16_t Mpu6050::readAccX(){
	auto msb = readRegister(ACCEL_XOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	convertAccelero(value);
	return value;
}

int16_t Mpu6050::readAccXRaw(){
	auto msb = readRegister(ACCEL_XOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	return value;
}

int16_t Mpu6050::readAccY(){
	auto msb = readRegister(ACCEL_YOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	convertAccelero(value);
	return value;
}

int16_t Mpu6050::readAccYRaw(){
	auto msb = readRegister(ACCEL_YOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	return value;
}

int16_t Mpu6050::readAccZ(){
	auto msb = readRegister(ACCEL_ZOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	convertAccelero(value);
	return value;
}

int16_t Mpu6050::readAccZRaw(){
	auto msb = readRegister(ACCEL_ZOUT_H);
	auto lsb = hwlib::i2c_read_transaction(sensor, sensorAddress).read_byte();
	int16_t value = concatenateBytes(msb, lsb);
	return value;
}

int16_t Mpu6050::readGyroX(){
	auto msb = readRegister(GYRO_XOUT_H);
	auto lsb = readRegister(GYRO_XOUT_L);
	int16_t value = concatenateBytes(msb, lsb);
	convertGyro(value);
	return value;
}

int16_t Mpu6050::readGyroY(){
	auto msb = readRegister(GYRO_YOUT_H);
	auto lsb = readRegister(GYRO_YOUT_L);
	int16_t value = concatenateBytes(msb, lsb);
	convertGyro(value);
	return value;
}

int16_t Mpu6050::readGyroZ(){
	auto msb = readRegister(GYRO_ZOUT_H);
	auto lsb = readRegister(GYRO_ZOUT_L);
	int16_t value = concatenateBytes(msb, lsb);
	convertGyro(value);
	return value;
}

int16_t Mpu6050::readGyroXRaw(){
	auto msb = readRegister(GYRO_XOUT_H);
	auto lsb = readRegister(GYRO_XOUT_L);
	return concatenateBytes(msb, lsb);
}

int16_t Mpu6050::readGyroYRaw(){
	auto msb = readRegister(GYRO_YOUT_H);
	auto lsb = readRegister(GYRO_YOUT_L);
	return concatenateBytes(msb, lsb);
}

int16_t Mpu6050::readGyroZRaw(){
	auto msb = readRegister(GYRO_ZOUT_H);
	auto lsb = readRegister(GYRO_ZOUT_L);
	return concatenateBytes(msb, lsb);
}

int16_t Mpu6050::readTemperature(){
	auto msb = readRegister(TEMP_OUT_H);
	auto lsb = readRegister(TEMP_OUT_L);
	auto value = concatenateBytes(msb, lsb);
	value = value / 340 + 31.53;
	return value;
}

void Mpu6050::convertGyro(int16_t & value){
	float input = value;
	input /= readGyroConfig();
	value = input;
}

void Mpu6050::convertAccelero(int16_t & value){
	float input = value;
	input *= 981;
	input /= readAcceleroConfig();
	value = input;
}

void Mpu6050::setAcceleroConfig(uint8_t afs_sel){
	if(afs_sel >= 0 && afs_sel <= 3){
		afs_sel = afs_sel << 3;
		const uint8_t configValue[2] = {ACCEL_CONFIG, afs_sel};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2);
	}else{
		const uint8_t configValue[2] = {ACCEL_CONFIG, 0};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2);
	}
}

int16_t Mpu6050::readAcceleroConfig(){
	auto config = readRegister(ACCEL_CONFIG);
	int16_t returnValue = 16384;
	config &= 0x18; // get rid of ST bits, which are not needed
	config = config >> 3; // shift the two desired bits all the way to the right for the appropriate int.
	returnValue = returnValue >> config;
	return returnValue;
}

void Mpu6050::setGyroConfig(uint8_t fs_sel){
	if(fs_sel >= 0 && fs_sel <= 3){
		fs_sel = fs_sel << 3;
		const uint8_t configValue[2] = {GYRO_CONFIG, fs_sel};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2);
	}else{
		const uint8_t configValue[2] = {GYRO_CONFIG, 0};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2); // write default of zero in case of unexpected input
	}
}

float Mpu6050::readGyroConfig(){
	uint8_t config = readRegister(GYRO_CONFIG);
	float returnValue;
	config = config << 3; // get rid of ST bits, which are not needed
	config = config >> 6; // shift the two desired bits all the way to the right for the appropriate int.
	hwlib::cout << config << hwlib::endl;
	if(config == 3){ returnValue = 16.4; }
	if(config == 2){ returnValue = 32.8; }
	if(config == 1){ returnValue = 65.5; }
	if(config == 0){ returnValue = 131.0; } // can't bitshift float values so hardcoded instead.
	return returnValue;
}

void Mpu6050::setConfig(uint8_t dlpf){
	if(dlpf >= 0 && dlpf <= 6){
		const uint8_t configValue[2] = {CONFIG, dlpf};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2);
	}else{
		const uint8_t configValue[2] = {CONFIG, 0};
		hwlib::i2c_write_transaction(sensor, sensorAddress).write(configValue, 2); // write default of zero in case of unexpected input
	}
}

uint8_t Mpu6050::readConfig(){
	auto config = readRegister(CONFIG);
	config &= 0b00000111;
	return config;
}
