#include "hwlib.hpp"
#include "stepper28BYJ48.hpp"


int main(){
  auto input0 = hwlib::target::pin_out( 3, 4 );
  auto input1 = hwlib::target::pin_out( 3, 5 );
  auto input2 = hwlib::target::pin_out( 0, 13 );
  auto input3 = hwlib::target::pin_out( 0, 12 );
  auto poort = hwlib::port_out_from( input0, input1, input2, input3 );
  auto motor = stepper28BYJ48( poort );

  hwlib::cout << "The steppermotor's inputs should be connected to Due pins 14-17 with input 1 connected to 14 and input 4 connected to 17" << hwlib::endl;
  hwlib::wait_ms(8000);

  hwlib::cout << "The motor's output shaft should make one full clockwise rotation, followed by a full counterclockwise rotation" << hwlib::endl;
  hwlib::wait_ms(8000);
  motor.turnClockwiseDegrees(360);
  hwlib::wait_ms(1000);
  motor.turnCounterClockwiseDegrees(360);
  hwlib::cout << "Testing sequence complete" << hwlib::endl;
}
