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