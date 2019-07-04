//          Copyright Youri de Vor 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef STEPPERMOTOR_HPP
#define STEPPERMOTOR_HPP

#include "hwlib.hpp"

/// @file

/// Library for implementing a steppermotor with 4 input pins and 8 steps through a hwlib::port_out.
///
/// This library contains functions to write values to the hwlib::port_out and turn the steppermotor
/// in either clockwise or counterclockwise direction. The rotations can be done in any given increment in steps.
/// The default is three if no amount of steps is given, because this is the biggest single step a 4 input, 8 step steppermotor can make.
/// There are two other rotation functions which turn the motors a given number of degrees.
class steppermotor {
private:
  /// A port consisting of 4 output pins.
  hwlib::port_out &port;

  /// An index variable used to select a step from the steps array.
  int8_t index;

  /// An unsigned integer value to which a step can be assigned to a step and to be written to the hwlib::port_out.
  uint8_t value;

  /// An array containing the 4 bit values of all 8 possible steps of a 4pin/4coil steppermotor.
  uint8_t steps[8];


public:
  /// Constructor
  ///
  /// Constructs a steppermotor object out of the given hwlib::port_out.
  steppermotor(hwlib::port_out & port);

  /// Writes a value to the hwlib::port_out.
  ///
  /// Writes the value-variable to the hwlib::port_out buffer and flushes the port with the buffer.
  virtual void writeValue();

  /// Turns the motor 3 steps in clockwise direction.
  ///
  /// Changes the value-variable to the third step in clockwise direction from the current step and applies this to the
  /// motor using the writeValue function.
  /// It is advised to not use this function in an otherwise (nearly) empty loop without additional waiting.
  /// This will cause the steppermotor to not turn at all due to a too high input speed.
  /// Use the version with built in loop instead.
  virtual void turnClockwise();

  /// Turns the motor 3 steps in counterclockwise direction.
  ///
  /// Changes the value-variable to the third step in counterclockwise direction from the current step in the array and applies this to the
  /// motor using the writeValue function.
  /// It is advised to not use this function in an otherwise (nearly) empty loop without additional waiting.
  /// This will cause the steppermotor to not turn at all due to a too high input speed.
  /// Use the version with built in loop instead.
  virtual void turnCounterClockwise();

  /// Turns the motor 'times' steps in clockwise direction.
  ///
  /// Takes a given amount of steps in clockwise direction using the same methods as the other turnClockwise function.
  virtual void turnClockwise(uint16_t times);

  /// Turns the motor 'times' steps in counterclockwise direction.
  ///
  /// Takes a given amount of steps in counterclockwise direction using the same methods as the other turnClockwise function.
  virtual void turnCounterClockwise(uint16_t times);

};

#endif
