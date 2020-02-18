#include "robot/small_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in small_bot header file
SmallBot::SmallBot(util::Position& _pos) : Bot(_pos){};

void SmallBot::driver() {
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3, directionType::fwd); //base
  movement::mech(lift_left, lift_right, Controller1.Axis2); //lift
  movement::mech(ramp, Controller1.ButtonL2, Controller1.ButtonL1); //ramp
  movement::mech(rollers_left, rollers_right, Controller1.ButtonR2, Controller1.ButtonR1); //rollers
  movement::digi_out(shift, Controller1.ButtonUp, Controller1.ButtonDown); //transmission
  movement::digi_out(shoot, Controller1.ButtonX); //shoot
  score(base_left, base_right, rollers_left, rollers_right, Controller1.ButtonA, 50);
}

void SmallBot::auton() {
  //TODO
  top_down_sucker(3, 3.5);
}

void SmallBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
  // aut.group_stop(base_left, base_right, brake);
}

void SmallBot::move_base(double pow, float lim, velocityUnits vel, rotationUnits rot) {
  aut.move_group_for(base_left, base_right, lim, rot, pow, vel);
  // aut.group_stop(base_left, base_right, brake);
}

void SmallBot::rotate_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel, false);
}

void SmallBot::rotate_base(double pow, float lim, velocityUnits vel) {
  aut.mech_rotate_gyro(g_sensor, base_left, base_right, lim, pow, vel);
  // aut.group_stop(base_left, base_left);
}

void SmallBot::move_lift(double pow, float lim, velocityUnits vel, rotationUnits rot) {
  aut.move_group_for(lift_left, lift_right, lim, rot, pow, vel);
  // aut.group_stop(lift_left, lift_right, hold);
}

void SmallBot::grab(bool intake, float revs) {
  if(!intake){
    revs = -revs;
  }
  aut.mech_rotate(rollers_left, rollers_right, revs, rotationUnits::rev, 100, velocityUnits::pct);
}

double SmallBot::gear_convert(double input) {
  // TODO
  return input;
}

void SmallBot::score(vex::motor_group b_left, vex::motor_group b_right, vex::motor_group r_left, vex::motor_group r_right, vex::controller::button toggle, double pow, velocityUnits v_units) {
  if (toggle.pressing()) {
    
    // b_left.rotateFor(directionType::fwd, 400, rotationUnits::deg, 20, velocityUnits::pct, false);
    // b_right.rotateFor(directionType::fwd, 400, rotationUnits::deg, 20, velocityUnits::pct, false);

    // r_left.rotateFor(directionType::rev, 800, rotationUnits::deg, 20, velocityUnits::pct, false);
    // r_right.rotateFor(directionType::fwd, 800, rotationUnits::deg, 20, velocityUnits::pct);

    b_left.spin(directionType::rev, pow, v_units);
    b_right.spin(directionType::rev, pow, v_units);

    r_left.spin(directionType::fwd, 100, velocityUnits::pct);
    r_right.spin(directionType::fwd, 100, velocityUnits::pct);

  }
  //since we are also calling these motor groups in other functions within the drive method we dont need to add brakes here
}

void SmallBot::move_ramp(double pow, directionType dir){
  ramp.setVelocity(pow, velocityUnits::pct);

  ramp.rotateFor(dir, 3, rotationUnits::rev);
  ramp.setVelocity(100, velocityUnits::pct);
}

void SmallBot::top_down_sucker(double dist, double height){
  //lift
  move_lift(80, height);

  //go front
  move_base(60, dist);

  //intake
  aut.move_group_double(rollers_left, rollers_right, 80, velocityUnits::pct, true);

  //slowly bring lift down until bottom out
  move_lift(10, -height);

  aut.group_stop(rollers_left, rollers_right);
}