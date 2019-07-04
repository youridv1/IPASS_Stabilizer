#include "stepper28BYJ48.hpp"

stepper28BYJ48::stepper28BYJ48(hwlib::port_out & port, uint16_t stepsPerRotation):
  steppermotor( port ),
  stepsPerRotation( stepsPerRotation )
{}

void stepper28BYJ48::turnClockwiseDegrees(uint16_t degrees){
  float steps = degrees / 360.0 * stepsPerRotation;
  uint16_t times = steps;
  turnClockwise(times);
}

void stepper28BYJ48::turnCounterClockwiseDegrees(uint16_t degrees){
  float steps = degrees / 360.0 * stepsPerRotation;
  uint16_t times = steps;
  turnCounterClockwise(times);
}
