#ifndef STEPPER28BYJ48_HPP
#define STEPPER28BYJ48_HPP

#include "steppermotor.hpp"

/// @file

/// A subclass based on steppermotor.
///
/// This is a subclass of steppermotor which adds the functionality of being able
///  to turn a given amount of degrees on top of the general steppermotor functions.
class stepper28BYJ48 : public steppermotor {
private:
  /// The amount of steps the motor has to take to complete one revolution of the output shaft.
  uint16_t stepsPerRotation;

public:
  /// Constructor
  ///
  /// Constructs a stepper28BYJ48 object out of the given hwlib::port_out and an
  /// amount of steps per rotation, which defaults to 4096.
  stepper28BYJ48(hwlib::port_out & port, uint16_t stepsPerRotation = 4096);

  /// Turns the motor a given amount of degrees in clockwise direction.
  ///
  /// Calculates the amount of steps needed to turn and rotates the motor that amount of steps.
  void turnClockwiseDegrees(uint16_t degrees);

  /// Turns the motor a given amount of degrees in counterclockwise direction.
  ///
  /// Calculates the amount of steps needed to turn and rotates the motor that amount of steps.
  void turnCounterClockwiseDegrees(uint16_t degrees);

};

#endif
