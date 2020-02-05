#ifndef UTIL_H
#define UTIL_H

#include "vex.h"

namespace util 
{
  int arr_length(vex::motor* arr);
  int arr_length(vex::digital_out* arr);
//   template <typename T> 
// int arr_length(T arr) {
//   return sizeof(arr) / sizeof(*arr);
// }

  void gyro_calibrate(vex::gyro sensor);

  enum class Side{top, bottom};
  enum class Color{red, blue};
  class Position{
  private:
    Side s;
    Color c;
  public:
    Position(Side _s, Color _c) : s{_s}, c{_c}{
      // s = _s;
      // c = _c;
    }
    Side getSide();

    Color getColor();
};
}

/*****************************
PID implementation (will be a class that is instantiated whenever a function uses PID)

https://www.teachmemicro.com/arduino-pid-control-tutorial/

This only needs to have something t return a 0 once the PID has been 
within acceptable range of desired val for x amount of time. So it returns a 0 once it ends

******************************/

#endif