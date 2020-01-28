#include "robot/big_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in big_bot header file
BigBot::BigBot(util::Position& _pos, robot::ControllerGroup& _cg) : Bot(_pos, _cg){};

void BigBot::driver(){
  movement::base_arcade(base_group, cg.get_first().Axis4, cg.get_first().Axis3);
  movement::mech(ramp_group, cg.get_first().Axis2);//ramp
  movement::mech(rollers_group, cg.get_first().ButtonA, cg.get_first().ButtonB);//rollers
  movement::digi_out(piston_group, cg.get_first().ButtonUp, cg.get_first().ButtonDown);//transmission
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