#include "robot/big_bot.h"
#include "movement.h"
#include "vex.h"

using namespace robot;
using namespace vex;


//Whoever uses this library would only have to implement these methods for their robot to work
//Most of the code for movement has already been done  in other files and motors are designate in big_bot header file
BigBot::BigBot(util::Position& _pos) : Bot(_pos){};

void BigBot::driver(){
  movement::base_arcade(base_left, base_right, Controller1.Axis4, Controller1.Axis3, directionType::fwd);
  movement::mech(ramp_l, ramp_r, Controller1.Axis2);//ramp
  movement::mech(rollers_l, rollers_r, Controller1.ButtonR2, Controller1.ButtonR1);//rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown);//transmission
  movement::digi_out(ramp_piston, Controller1.ButtonX, Controller1.ButtonY);//ramp open
}

void BigBot::auton() {
  //open ramp
  open_ramp();
  task::sleep(PAUSE);

  //move front to get 4 cubes
  move_base(100, 2.0);
  task::sleep(PAUSE);
  aut.move_group(rollers_l, 100);
  aut.move_group(rollers_r, -100);

  for(int i=0; i<4; i++){
    move_base(30, 0.5);
    task::sleep(PAUSE);
  }
  aut.group_stop(rollers_l, rollers_r);

  //move back a bit
  move_base(100, 6.0);
  task::sleep(PAUSE);

  //turn to face away from other bot
  rotate_base(50, 90);//these rotates can leverage the position object
  task::sleep(PAUSE);

  //move forward 1 tile
  move_base(100, 1.0);
  task::sleep(PAUSE);

  //turn to face the cubes
  rotate_base(50, -90);
  task::sleep(PAUSE);

  //move front to grab 4 cubes
  move_base(100, 1.0);
  task::sleep(PAUSE);
  grab();
  for(int i=0; i<4; i++){
    move_base(30, 0.5);
    task::sleep(PAUSE);
  }
  aut.group_stop(rollers_l, rollers_r);

  //turn facing the wall
  rotate_base(50, 180);
  task::sleep(PAUSE);

  //move front towards wall
  move_base(100, 4.0);
  task::sleep(PAUSE);

  //turn towards corner
  rotate_base(50, 90);
  task::sleep(PAUSE);

  //move front to get into scoring position
  move_base(40, 1.0);
  task::sleep(PAUSE);

  //move ramp to score
  move_ramp(70);
}

void BigBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
}

void BigBot::move_base(double pow, float lim, velocityUnits vel, rotationUnits rot){
  aut.move_group_for(base_left, base_right, lim, rot, pow, vel);
}


void BigBot::rotate_base(double pow, velocityUnits vel) {
  pow = gear_convert(pow);
  aut.move_group(base_left, pow, velocityUnits::pct);
  aut.move_group(base_right, -pow, velocityUnits::pct);
}

void BigBot::rotate_base(double pow, float lim, velocityUnits vel) {
  pow = gear_convert(pow);
  // aut.mech_rotate(base_left, base_right, lim, rotationUnits::rev, pow, vel);//using encoders

  //using gyro
  // aut.mech_rotate_gyro(t.H, base_left, base_right, lim, pow, vel);
  aut.mech_rotate_dual_gyro(t.H, t.G, base_left, base_right, lim, pow, vel);

}

void BigBot::grab(bool intake, float revs) {
  aut.mech_rotate(rollers_l, rollers_r, revs, rotationUnits::rev, 100, velocityUnits::pct);
}

double BigBot::gear_convert(double input){
  return input * (5/3);
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
    aut.move_group_for_bumper(bump_port, ramp_l, ramp_r, speed, vel);
  } 
  // else { // hold lift
  //   aut.group_stop(ramp_l, ramp_r, brakeType::hold);
  // }
}

void BigBot::open_ramp(){
  //set on toque the base
  aut.activate_piston(Piston, true);
  //intake out
  aut.move_group(rollers_l,-100);
  aut.move_group(rollers_r, 100);

  //piston for ramp
  aut.activate_piston(ramp_piston, true);
  task::sleep(1000);

  aut.group_stop(rollers_l, rollers_r);
}