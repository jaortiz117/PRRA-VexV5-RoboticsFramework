#include "util.h"
#include "vex.h"

int util::arr_length(vex::motor *arr) { return sizeof(arr) / sizeof(*arr); }

int util::arr_length(vex::digital_out *arr) {
  return sizeof(arr) / sizeof(*arr);
}

float util::floating_abs(float n){
  if(n < 0.0)
    return -1.0 * n;

  return n;
}

util::Side util::Position::getSide() { return s; }

util::Color util::Position::getColor() { return c; }

void util::gyro_calibrate(vex::gyro sensor){
  sensor.startCalibration();
  while(sensor.isCalibrating()){
    task::sleep(5);
  }

  // sensor.resetRotation();
}