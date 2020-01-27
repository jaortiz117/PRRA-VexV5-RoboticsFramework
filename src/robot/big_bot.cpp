#include "robot/big_bot.h"
#include "movement.h"

using namespace robot;

BigBot::BigBot(util::Position& _pos, robot::ControllerGroup& _cg) : Bot(_pos, _cg){

  vex::motor base_left[3]= {BaseLeft1, BaseLeft2, BaseLeft3};
  vex::motor base_right[3]= {BaseRight1, BaseRight2, BaseRight3};
  MotorGroup base = MotorGroup(base_left, base_right);
  BigBot::base_group = &base;

  vex::motor ramp_l[1]= {RampL};
  vex::motor ramp_r[1]= {RampR};
  MotorGroup ramp = MotorGroup(ramp_l, ramp_r);
  BigBot::ramp_group = &ramp;

  vex::motor rollers_l[2]= {RollerL1, RollerL2};
  vex::motor rollers_r[2]= {RollerR1, RollerR2};
  MotorGroup roll = MotorGroup(rollers_l, rollers_r);
  BigBot::rollers_group = &roll;

  vex::digital_out digi[1] = {Piston};
  DigitalOutGroup pist = DigitalOutGroup(digi, digi);
  BigBot::piston_group = &pist;
}

void BigBot::driver(){
  movement::base_arcade(*base_group, cg.get_first().Axis1, cg.get_first().Axis2);
  movement::mech(*ramp_group, cg.get_first().Axis2);//ramp
  movement::mech(*rollers_group, cg.get_first().ButtonA, cg.get_first().ButtonB);//rollers
  movement::digi_out(*piston_group, cg.get_first().ButtonX, cg.get_first().ButtonY);//transmission
}

void BigBot::auton() {
  //TODO
}

void BigBot::move_base(double power, velocityUnits vel) {
  //TODO
}

void BigBot::rotate_base(double power, velocityUnits vel) {
  //TODO
}

void BigBot::grab(bool intake, float revs) {
  //TODO
}