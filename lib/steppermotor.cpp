//          Copyright Youri de Vor 2018 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "steppermotor.hpp"

steppermotor::steppermotor(hwlib::port_out & port):
  port( port ),
  index( 0 ),
  value( 1 ),
  steps{1, 3, 2, 6, 4, 12, 8, 9}
{}

void steppermotor::writeValue(){
  port.write( value );
  port.flush();
}


void steppermotor::turnClockwise(){
  index += 3;
  if(index > 7){
    index -= 8;
  }
  value = steps[index];
  writeValue();
  hwlib::wait_ms(2);
}

void steppermotor::turnCounterClockwise(){
  index -= 3;
  if(index < 0){
    index += 8;
  }
  value = steps[index];
  writeValue();
  hwlib::wait_ms(2);
}

void steppermotor::turnClockwise(uint16_t times){
  while(times >= 3){
    turnClockwise();
    times -= 3;
    hwlib::wait_ms(2);
  }
  if(times > 0){
    index += times;
    if(index > 7){
      index -= 8;
    }
    value = steps[index];
    writeValue();
    hwlib::wait_ms(2);
  }
}

void steppermotor::turnCounterClockwise(uint16_t times){
  while(times >= 3){
    turnCounterClockwise();
    times -= 3;
  }
  if( times > 0){
    index -= times;
    if(index < 0){
      index += 8;
    }
    value = steps[index];
    writeValue();
    hwlib::wait_ms(2);
  }
}
