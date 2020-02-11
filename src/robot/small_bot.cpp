#include "robot/small_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in small_bot header file
SmallBot::SmallBot(util::Position& _pos) : Bot(_pos){};

void SmallBot::driver() {
  movement::base_arcade(base_left, base_right, Controller1.Axis3, Controller1.Axis4, directionType::rev); //base
  movement::mech(lift_left, lift_right, Controller1.Axis2); //lift
  movement::mech(ramp, Controller1.ButtonL2, Controller1.ButtonL1); //ramp
  movement::mech(rollers_left, rollers_right, Controller1.ButtonR2, Controller1.ButtonR1); //rollers
  movement::digi_out(shift, Controller1.ButtonUp, Controller1.ButtonDown); //transmission
  movement::digi_out(shoot, Controller1.ButtonX, Controller1.ButtonB); //shoot
  movement::score(base_left, base_right, rollers_left, rollers_right, Controller1.ButtonA);
}

void SmallBot::auton() {
  // TODO
  aut.group_stop(base_left, base_right);
}

void SmallBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
  aut.group_stop(base_left, base_right, brake);
}

void SmallBot::move_base(double pow, float lim, velocityUnits vel, rotationUnits rot) {
  aut.move_group_for(base_left, base_right, lim, rot, pow, vel);
  aut.group_stop(base_left, base_right, brake);
}

// void SmallBot::rotate_base(double pow, velocityUnits vel) {
//   // TODO
// }

// void SmallBot::rotate_base(double pow, float lim, velocityUnits vel, rotationUnits rot) {
//   aut.mech_rotate_gyro(gyro_port, base_left, base_right, lim, pow, vel);
//   aut.group_stop(base_left, base_left);
// }

void SmallBot::move_lift(double pow, float lim, velocityUnits vel, rotationUnits rot) {
  aut.move_group_for(base_left, base_right, lim, rot, lim, vel);
  aut.group_stop(lift_left, lift_right, hold);
}

void SmallBot::grab(bool intake, float revs) {
  // TODO
}

double SmallBot::gear_convert(double input) {
  // TODO
  return -1.0;
}