#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"

/// @file

/// Library for implementing a MPU6050 chip through i2c
///
/// The library contains functions to read data from the MPU6050's registers
/// in either raw format or converted into more readable units, as well as containing
/// functions to configure and read the sensitivity of the Accelerometer and Gyroscope.
/// Functions for configuring and reading the dlpf bits are also provided.
/// Any information regarding registers and methods used in this library can be
/// found in the Invensense MPU6050 Datasheet and Register Map respectively.

class Mpu6050 {
private:
  /// The i2c Bus Bit Banged SCL SDA object used
  hwlib::i2c_bus_bit_banged_scl_sda &sensor;
  /// The MPU6050's Master Adress.
  ///
  /// 0x68 when the AD0 pin on the chip's board is low and 0x69 when said
  /// pin is high.
  const uint8_t sensorAddress;

  // Configuration Registers
  const uint8_t CONFIG =         0x1A;
  const uint8_t GYRO_CONFIG =    0x1B;
  const uint8_t ACCEL_CONFIG =   0x1C;

  // Accelerometer Registers
  const uint8_t ACCEL_XOUT_H =   0x3B;
  const uint8_t ACCEL_XOUT_L =   0x3C;
	const uint8_t ACCEL_YOUT_H =   0x3D;
	const uint8_t ACCEL_YOUT_L =   0x3E;
	const uint8_t ACCEL_ZOUT_H =   0x3F;
	const uint8_t ACCEL_ZOUT_L =   0x40;

  // Temperature Sensor Registers
	const uint8_t TEMP_OUT_H =     0x41;
	const uint8_t TEMP_OUT_L =     0x42;

  // Gyroscope Registers
	const uint8_t GYRO_XOUT_H =    0x43;
	const uint8_t GYRO_XOUT_L =    0x44;
	const uint8_t GYRO_YOUT_H =    0x45;
	const uint8_t GYRO_YOUT_L =    0x46;
	const uint8_t GYRO_ZOUT_H =    0x47;
	const uint8_t GYRO_ZOUT_L =    0x48;

  // Powermanagement Register
  const uint8_t PWR_MGMT_1 =     0x6B;

  // Who Am I Register (Contains the Master Adress referred to in code as sensorAdress)
	const uint8_t WHO_AM_I =       0x75;

public:
  /// Constructor
  ///
  /// Constructs an i2c object for the Mpu6050 using an i2c_bus_bit_banged_scl_sda bus and a 7-bit address, which defaults to 0x68.
  Mpu6050(hwlib::i2c_bus_bit_banged_scl_sda &sensor, const uint8_t &sensorAdress = 0x68);

  /// Selects register to write to.
  ///
  /// Writes a given register address to the i2c bus to select a register for the next read transaction.
  virtual void selectRegister(const uint8_t &registerAdress);

  /// Disables the MPU6050's built in sleep mode, which allows the registers to be updated.
  ///
  /// Writes a 0 to the PWR_MGMT_1 register do disable sleep mode.
  /// Useful if you would like the registers to be updated at all.
  virtual void disableSleep();

  /// Enables the MPU6050's built in sleep mode, which stops  the registers from being updated.
  ///
  /// Writes a 0 to the PWR_MGMT_1 register do disable sleep mode.
  /// Useful if you would like to save power.
  virtual void enableSleep();

  /// Gets data from a given register address.
  ///
  /// Gets data from the register corresponding to the given address and returns a uint8_t.
  virtual uint8_t readRegister(const uint8_t &registerAdress);

  /// Concatenates an int16_t from two given uint8_t's.
  ///
  /// Returns an int16_t which most significant byte consists of the given msb
  /// and which least significant byte consists of the given lsb.
  /// Useful in case one measurement is split up into two 8 bit registers like all measurements from the MPU6050.
  virtual int16_t concatenateBytes(const uint8_t &msb, const uint8_t &lsb);

  /// Gets the acceleration along the X-axis.
  ///
  /// Reads the ACCEL_XOUT_H and ACCEL_XOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to cm/s^2.
  virtual int16_t readAccX();

  /// Gets the acceleration along the Y-axis.
  ///
  /// Reads the ACCEL_YOUT_H and ACCEL_YOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to cm/s^2.
  virtual int16_t readAccY();

  /// Gets the acceleration along the Z-axis.
  ///
  /// Reads the ACCEL_ZOUT_H and ACCEL_ZOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to cm/s^2.
  virtual int16_t readAccZ();

  /// Gets the acceleration along the X-axis.
  ///
  /// Reads the ACCEL_XOUT_H and ACCEL_XOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readAccXRaw();

  /// Gets the acceleration along the Y-axis.
  ///
  /// Reads the ACCEL_YOUT_H and ACCEL_YOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readAccYRaw();

  /// Gets the acceleration along the Y-axis.
  ///
  /// Reads the ACCEL_YOUT_H and ACCEL_YOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readAccZRaw();

  /// Gets the angular velocity around the X-axis.
  ///
  /// Reads the GYRO_XOUT_H and GYRO_XOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to degrees per second.
  virtual int16_t readGyroX();

  /// Gets the angular velocity around the Y-axis.
  ///
  /// Reads the GYRO_YOUT_H and GYRO_YOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to degrees per second.
  virtual int16_t readGyroY();

  /// Gets the angular velocity around the Z-axis.
  ///
  /// Reads the GYRO_ZOUT_H and GYRO_ZOUT_L and concatenates these values using the concatenateBytes function.
  /// Converts to degrees per second.
  virtual int16_t readGyroZ();

  /// Gets the angular velocity around the X-axis.
  ///
  /// Reads the GYRO_XOUT_H and GYRO_XOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readGyroXRaw();

  /// Gets the angular velocity around the Y-axis.
  ///
  /// Reads the GYRO_YOUT_H and GYRO_YOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readGyroYRaw();

  /// Gets the angular velocity around the Z-axis.
  ///
  /// Reads the GYRO_ZOUT_H and GYRO_ZOUT_L and concatenates these values using the concatenateBytes function.
  virtual int16_t readGyroZRaw();

  /// Gets the measured temperature.
  ///
  /// Reads the TEMP_OUT_H and TEMP_OUT_L and concatenates these values using the concatenateBytes function.
  /// Converts into degrees Celcius.
  virtual int16_t readTemperature();

  /// Converts to cm/s^2
  ///
  /// Converts raw Accelerometer data to cm/s^2 using the current ACCEL_CONFIG value.
  virtual void convertAccelero(int16_t & value);

  /// Converts to degrees per second
  ///
  /// Converts raw Gyroscope data to degrees per second using the current GYRO_CONFIG value.
  virtual void convertGyro(int16_t & value);

  /// Configures the ACCEL_CONFIG register.
  ///
  /// Writes a given value between 0 and 3 to the afs_sel portion of the ACCEL_CONFIG
  /// register. Defaults to writing 0 when given value is not applicable by being out of range.
  virtual void setAcceleroConfig(uint8_t afs_sel);

  /// Configures the GYRO_CONFIG register.
  ///
  /// Writes a given value between 0 and 3 to the fs_sel portion of the GYRO_CONFIG
  /// register. Defaults to writing 0 when given value is not applicable by being out of range.
  virtual void setGyroConfig(uint8_t fs_sel);

  /// Configures the Digital Low Pass Filter register.
  ///
  /// Writes a given value between 0 and 3 to the dlpf portion of the CONFIG
  /// register. Defaults to writing 0 when given value is not applicable by
  /// being out of range.
  virtual void setConfig(uint8_t dlpf);

  /// Returns the sensitivity of the Accelerometer.
  ///
  /// Reads the afs_sel bits out of the ACCEL_CONFIG register and calculates the
  /// corresponding sensitivity of the Accelerometer.
  /// Useful to be able to divide by the current sensitivity while converting the raw
  /// Accelerometer data to more readable units.
  virtual int16_t readAcceleroConfig();

  /// Returns the sensitivity of the Gyroscope.
  ///
  /// Reads the fs_sel bits out of the GYRO_CONFIG register and calculates the
  /// corresponding sensitivity of the Gyroscope.
  /// Useful to be able to divide by the current sensitivity while converting the raw
  /// Gyroscope data to more readable units.
  virtual float readGyroConfig();

  /// Returns the dlpf_cfg value
  ///
  /// Reads the dlpf_cfg bits out of the CONFIG register and returns the value.
  /// Useful for checking in which mode the dlpf is.
  virtual uint8_t readConfig();
};

#endif
