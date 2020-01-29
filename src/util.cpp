#include "util.h"
#include "vex.h"

int util::arr_length(vex::motor *arr) { return sizeof(arr) / sizeof(*arr); }

int util::arr_length(vex::digital_out *arr) {
  return sizeof(arr) / sizeof(*arr);
}

util::Side util::Position::getSide() { return s; }

util::Color util::Position::getColor() { return c; }