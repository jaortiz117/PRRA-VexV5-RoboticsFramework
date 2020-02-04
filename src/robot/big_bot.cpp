#include "robot/big_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in big_bot header file
BigBot::BigBot(util::Position& _pos) : Bot(_pos){};

double BigBot::gear_convert(double input){
  return input*(5/3);
}

void BigBot::driver(){
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3);
  movement::mech(ramp_l, ramp_r, Controller1.Axis2);//ramp
  movement::mech(rollers_l, rollers_r, Controller1.ButtonR2, Controller1.ButtonR1);//rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown);//transmission
}

void BigBot::auton() {
  // util::gyro_calibrate(g_sensor);
  // move_base(50);
  // rotate_base(50, 1.0);
  // aut.move_group_for(base_left, base_right, gear_convert(2), rotationUnits::rev, 50, velocityUnits::pct);//TODO in move_base
  move_ramp(-50);

  //TODO make conversion for gears in lim for all internal functions

  //TODO
}

void BigBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
}

//TODO other move_base
void BigBot::move_base(double pow, float lim,
           velocityUnits vel, rotationUnits rot){
             //TODO
           }

void BigBot::rotate_base(double pow, velocityUnits vel) {
  pow = gear_convert(pow);
  aut.move_group(base_left, pow, velocityUnits::pct);
  aut.move_group(base_right, -pow, velocityUnits::pct);
}

void BigBot::rotate_base(double pow, float lim, 
velocityUnits vel, rotationUnits rot) {
  // aut.move_group(base_left, 100, velocityUnits::pct);
  // aut.move_group(base_right, -100, velocityUnits::pct);
  pow = gear_convert(pow);
  aut.mech_rotate(base_left, base_right, lim, rot, pow, vel);
}

//TODO other rotate_base

void BigBot::grab(bool intake, float revs) {
  //TODO
}

void BigBot::move_ramp(double speed, velocityUnits vel) {
  if(speed >= 0) { // move forward, stop with encoder
    if(ramp_l.rotation(rotationUnits::rev) < 2) {
      aut.move_group_double(ramp_l, ramp_r, speed);
    } 
    else if(ramp_l.rotation(rotationUnits::rev) < 3) {
      aut.move_group_double(ramp_l, ramp_r, speed/2);
    } 
    else if(ramp_l.rotation(rotationUnits::rev) <= 4) {
      aut.move_group_double(ramp_l, ramp_r, speed/4);
    } 
    else {
      aut.group_stop(ramp_l, ramp_r, brakeType::hold);
    }
  } 
  else if(speed < 0) { // move backwards, stop with bumper
    aut.move_group_for(ramp_btn, ramp_l, ramp_r, speed, vel);
  } 
  // else { // hold lift
  //   aut.group_stop(ramp_l, ramp_r, brakeType::hold);
  // }
}
