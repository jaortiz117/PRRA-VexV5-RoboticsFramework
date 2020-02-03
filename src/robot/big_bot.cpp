#include "robot/big_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in big_bot header file
BigBot::BigBot(util::Position& _pos) : Bot(_pos){};

void BigBot::driver(){
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3);
  movement::mech(ramp_l, ramp_r, Controller1.Axis2);//ramp
  movement::mech(rollers_l, rollers_r, Controller1.ButtonR2, Controller1.ButtonR1);//rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown);//transmission
}

void BigBot::auton() {
  move_base(50);
  //TODO
}

void BigBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
}

//TODO other move_base

void BigBot::rotate_base(double pow, velocityUnits vel) {
  aut.move_group(base_left, 100, velocityUnits::pct);
  aut.move_group(base_right, -100, velocityUnits::pct);
}

void BigBot::rotate_base(double pow, float lim, 
velocityUnits vel, rotationUnits rot) {
  // aut.move_group(base_left, 100, velocityUnits::pct);
  // aut.move_group(base_right, -100, velocityUnits::pct);

  aut.mech_rotate(base_left, base_right, lim, rot, pow, vel);
}

//TODO other rotate_base

void BigBot::grab(bool intake, float revs) {
  //TODO
}