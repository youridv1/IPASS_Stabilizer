//          Copyright Youri de Vor 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

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
