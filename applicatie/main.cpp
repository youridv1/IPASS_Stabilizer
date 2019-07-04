#define DEADZONE 2000

#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "stepper28BYJ48.hpp"


int main(){
  auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
  auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
  auto mpu = Mpu6050(bus, 0x68);
  hwlib::wait_ms( 500 );

  mpu.disableSleep();
  mpu.setGyroConfig(0);
  mpu.setAcceleroConfig(0);
  mpu.setConfig(0);

  auto input0 = hwlib::target::pin_out( 3, 4 );
  auto input1 = hwlib::target::pin_out( 3, 5 );
  auto input2 = hwlib::target::pin_out( 0, 13 );
  auto input3 = hwlib::target::pin_out( 0, 12 );
  auto poort0 = hwlib::port_out_from( input0, input1, input2, input3 );
  auto motor0 = stepper28BYJ48( poort0 );

  auto input4 = hwlib::target::pin_out( 0, 9 );
  auto input5 = hwlib::target::pin_out( 1, 25 );
  auto input6 = hwlib::target::pin_out( 2, 28 );
  auto input7 = hwlib::target::pin_out( 2, 26 );
  auto poort1 = hwlib::port_out_from( input4, input5, input6, input7 );
  auto motor1 = stepper28BYJ48( poort1 );

  int16_t AccY = 0;
  int16_t AccZ = 0;

  for(;;)
  {
    AccY = mpu.readAccYRaw();
    AccZ = mpu.readAccZRaw();
    if(AccY > DEADZONE)
    {
      motor0.turnCounterClockwise();
    }
    else if(AccY < -DEADZONE)
    {
      motor0.turnClockwise();
    }
    if(AccZ > DEADZONE)
    {
      motor1.turnCounterClockwise();
    }
    else if(AccZ < -DEADZONE)
    {
      motor1.turnClockwise();
    }
    hwlib::wait_ms(1);
  }
}
