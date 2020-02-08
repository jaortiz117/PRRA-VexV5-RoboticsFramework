#include "robot/small_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in big_bot header file
SmallBot::SmallBot(util::Position& _pos) : Bot(_pos){};

void SmallBot::driver() {
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3); //base
  movement::mech(lift_left, lift_right, Controller1.Axis2); //lift
  movement::mech(ramp, Controller1.ButtonL2, Controller1.ButtonL1); //ramp
  movement::mech(rollers_left, rollers_right, Controller1.ButtonR2, Controller1.ButtonR1); //rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown); //transmission
}

// for back axis3
// sides axis1
// lift  L1 L2
// rollers R1 R2
// ramp axis2

void SmallBot::auton() {
  // TODO
  aut.group_stop(base_left, base_right);
}

// TODO
// void move_base(double pow, velocityUnits vel = velocityUnits::pct) override;
// void move_base(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev) override;
// void rotate_base(double pow, velocityUnits vel = velocityUnits::pct) override;
// void rotate_base(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev) override;
// void move_lift(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev);
// void grab(bool intake = true, float revs = 10.0) override;
// double gear_convert(double input);