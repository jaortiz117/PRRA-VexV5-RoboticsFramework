#ifndef UTIL_H
#define UTIL_H

#include "vex.h"

namespace util 
{
  int arr_length(vex::motor* arr);
  int arr_length(vex::digital_out* arr);
  float floating_abs(float n);
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

#endif