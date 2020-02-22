#include "robot/small_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;

//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in small_bot header file
SmallBot::SmallBot(util::Position& _pos) : Bot(_pos){};

void SmallBot::driver() {
  shift.set(false);
  shoot.set(false);
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3, directionType::fwd); //base
  movement::mech(lift_left, lift_right, Controller1.Axis2); //lift
  movement::mech(ramp, Controller1.ButtonL2, Controller1.ButtonL1); //ramp
  movement::mech_slower(ramp, Controller1.ButtonLeft, Controller1.ButtonRight); //ramp slower
  movement::mech(rollers_left, rollers_right, Controller1.ButtonR2, Controller1.ButtonR1); //rollers
  movement::digi_out(shift, Controller1.ButtonUp, Controller1.ButtonDown); //transmission
  movement::digi_out(shoot, Controller1.ButtonX); //shoot
  score(base_left, base_right, rollers_left, rollers_right, Controller1.ButtonA, 50); 
}

void SmallBot::auton() {
  
  shift.set(false);
  shoot.set(false);
  unlock_ramp();
  task::sleep(500);
  aut.move_group_double(rollers_left, rollers_right, 60, velocityUnits::pct, true);
  move_base(30, 2.5, velocityUnits::pct, rotationUnits::rev); //move to cube
  aut.group_stop(rollers_left, rollers_right);
  grab(true, 1.5); //grab cube
  top_down_sucker(3.5, 2.6); //grab cube tower (dist, height)
  rotate_base(70, -95); //turn robot towars score cube
  //aut.move_group_double(rollers_left, rollers_right, 60);
  move_base(30, 2.9, velocityUnits::pct, rotationUnits::rev); //move towards score cube
  //aut.group_stop(rollers_left, rollers_left);
  grab(true, 3); //grab score cube
  rotate_base(30, -7.1, velocityUnits::pct); //turn robot towars goal
  move_base(55, 3.55, velocityUnits::pct, rotationUnits::rev); //move towards goal
  task::sleep(1500);
  
  move_ramp(25, 2.85, fwd); //tilt ramp forward
  task::sleep(2000);
  move_base(18, 0.8, velocityUnits::pct, rotationUnits::rev); //place tower
  grab(false, 0.7); //let go of tower
  //move_ramp(15, 1.4, directionType::rev); //tilt ramp backwards
  score_auton(base_left, base_right, rollers_left, rollers_right); //move back and reverse rollers
  
  // grab(false, 4);
  // move_lift(50, 1);
  // grab(false, 4);
  // move_lift(50, 1);
  // grab(false, 4);
  // move_lift(50, 1);
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
  color_manage(util::Color::red, lim);
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

    r_left.spin(directionType::fwd, 25, velocityUnits::pct); //100
    r_right.spin(directionType::fwd, 25, velocityUnits::pct);

  }
  //since we are also calling these motor groups in other functions within the drive method we dont need to add brakes here
}

void SmallBot::score_auton(vex::motor_group b_left, vex::motor_group b_right, vex::motor_group r_left, vex::motor_group r_right) {
  b_left.rotateFor(directionType::rev, 400, rotationUnits::deg, 20, velocityUnits::pct, false);
  b_right.rotateFor(directionType::rev, 400, rotationUnits::deg, 20, velocityUnits::pct, false);

  r_left.rotateFor(directionType::rev, 800, rotationUnits::deg, 15, velocityUnits::pct, false);
  r_right.rotateFor(directionType::fwd, 800, rotationUnits::deg, 15, velocityUnits::pct);
}


void SmallBot::move_ramp(double pow, directionType dir){
  ramp.setVelocity(pow, velocityUnits::pct);

  ramp.rotateFor(dir, 2.8, rotationUnits::rev);
  ramp.setVelocity(100, velocityUnits::pct);
}

void SmallBot::move_ramp(double pow, float lim, directionType dir) {
  ramp.setVelocity(pow, velocityUnits::pct);

  ramp.rotateFor(dir, lim, rotationUnits::rev);
  ramp.setVelocity(100, velocityUnits::pct);
}

void SmallBot::top_down_sucker(double dist, double height){
  //lift

  move_lift(60, height);

  //go front
  move_base(60, dist);

  //intake
  aut.move_group_double(rollers_left, rollers_right, 60, velocityUnits::pct, true);

  //slowly bring lift down until bottom out
  move_lift(10, -(height-height*0.08));
  task::sleep(1580);

  aut.group_stop(rollers_left, rollers_right);
}

void SmallBot::unlock_ramp() {
  aut.move_group(lift_left, -85);
  aut.move_group(lift_right, -85);
  task::sleep(1800);
  aut.group_stop(lift_left, lift_right);
}