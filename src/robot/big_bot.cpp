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
  movement::mech(rollers_l, rollers_r, Controller1.ButtonA, Controller1.ButtonB);//rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown);//transmission
}

void BigBot::auton() {
  //TODO
}

void BigBot::move_base(double pow, velocityUnits vel) {
  //TODO
}

void BigBot::rotate_base(double pow, velocityUnits vel) {
  //TODO
}

void BigBot::grab(bool intake, float revs) {
  //TODO
}