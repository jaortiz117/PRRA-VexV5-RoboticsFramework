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

void BigBot::skills_auton(){
  //open ramp
  open_ramp();
  task::sleep(1000);

  //coger filas de 4 cubos-----
  aut.move_group(rollers_l, 100);
  aut.move_group(rollers_r, -100);
  move_base(100, 7.0);
  task::sleep(PAUSE);
  //coger filas de 4 cubos-----

  //get rid of obstructions------
  aut.group_stop(rollers_l, rollers_r);
  move_base(70, 3.0);
  aut.move_group(rollers_l, 100);
  aut.move_group(rollers_r, -100);
  //get rid of obstructions------

  //grab line on other side-----
  move_base(60, 7.2);
  task::sleep(600);
  aut.group_stop(rollers_l, rollers_r);
  //grab line on other side-----


  //score
  rotate_base(45,-40);//towards corner
  move_base(70, 5.1);
  task::sleep(300);

  //SCORE!!!
  grab(false, 0.5);
  move_ramp(50);
  task::sleep(1000);
  move_base(40, -3.2);

  
  //acomodarse filas de 4-----
  rotate_base(45,-115);

  move_base(100, 2);
  
  //crash with wall
  move_base(100,-4.0);
  task::sleep(300);

  //ramp down
  move_ramp(-50);

  //acomodarse filas de 4-----

  //get remaining cube line
  //coger filas de 4 cubos-----
  aut.move_group(rollers_l, 100);
  aut.move_group(rollers_r, -100);
  move_base(100, 7.0);
  task::sleep(PAUSE);
  //coger filas de 4 cubos-----

  //get rid of obstructions------
  aut.group_stop(rollers_l, rollers_r);
  move_base(60, 3.0);
  aut.move_group(rollers_l, 100);
  aut.move_group(rollers_r, -100);
  //get rid of obstructions------

  //grab line on other side-----
  move_base(100, 7.2);
  task::sleep(900);
  aut.group_stop(rollers_l, rollers_r);
  //grab line on other side-----

}

void BigBot::auton() {
  //open ramp
  open_ramp();
  task::sleep(1000);

  // //turn right towards single cube
  // rotate_base(35,38);
  // task::sleep(PAUSE);

  // //take cube from corner
  // aut.move_group(rollers_l, 100);
  // aut.move_group(rollers_r, -100);
  // move_base(30, 2);
  // task::sleep(500);

  // //move back a bit
  // move_base(50, -2);
  // aut.group_stop(rollers_l, rollers_r);

  // //rotate left
  // rotate_base(35, -30);

  // //crash with wall
  // aut.move_group(rollers_l, 100);
  // aut.move_group(rollers_r, -100);
  // move_base(50, -2);

  //move front to get 4 cubes
  aut.move_group(rollers_l, 80);
  aut.move_group(rollers_r, -80);
  move_base(100, 7.5);
  task::sleep(900);
  aut.group_stop(rollers_l, rollers_r);

  // //turn to face post
  // rotate_base(40, -15);//these rotates can leverage the position object
  // task::sleep(PAUSE);

  // //move front to get cubes on post
  // aut.move_group(rollers_l, 100);
  // aut.move_group(rollers_r, -100);
  // move_base(50.0, 2.5);
  // task::sleep(300);

  // aut.group_stop(rollers_l, rollers_r);

  // //mover un poco atras
  // move_base(50, -2.0);
  // task::sleep(PAUSE);

  // //rota to other cube
  // rotate_base(25,15);

  // //coger cubo en frente
  // aut.move_group(rollers_l, 100);
  // aut.move_group(rollers_r, -100);
  // move_base(50, 2.5);
  // task::sleep(200);

  //mover hacia atras
  move_base(100, -5);
  aut.group_stop(rollers_l, rollers_r);

  //rotate right
  rotate_base(40,50);
  task::sleep(PAUSE);

  //mover un poco atras
  move_base(75, -4.2);

  //rotate left
  rotate_base(40, -45);

  //crash with wall
  aut.move_group(rollers_l, 80);
  aut.move_group(rollers_r, -80);
  move_base(80, -2);

  //move front to get 4 cubes
  move_base(60, 7.2);
  // move_base(60, 5.2);//if grab center post is enabled, enable this and disable line above
  task::sleep(500);

  aut.group_stop(rollers_l, rollers_r);

  // //grab center post cube------------------------
  // //turn to face post
  // rotate_base(30, 15);//these rotates can leverage the position object

  // //move front to get cubes on post
  // aut.move_group(rollers_l, 100);
  // aut.move_group(rollers_r, -100);
  // move_base(50.0, 1.5);
  // task::sleep(PAUSE);

  // aut.group_stop(rollers_l, rollers_r);

  // //mover un poco atras
  // move_base(50, -1.5);

  // //rota to other cube
  // rotate_base(25,-15);
  // //center post cube-----------------------------
  
  //pyramid------------------------------
  //move back a bit
  move_base(70, -2);

  //turn left facing pyramid
  rotate_base(40,-35);
  task::sleep(PAUSE);

  //take cube from pyramid corner
  aut.move_group(rollers_l, 80);
  aut.move_group(rollers_r, -80);
  move_base(50, 2.5);
  task::sleep(500);

  //move back a bit
  move_base(70, -3.5);
  aut.group_stop(rollers_l, rollers_r);

  //turn right straight back home
  rotate_base(40,32);

  //pyramid------------------------------

  //move to goal
  move_base(50, -3.3);
  aut.group_stop(rollers_l, rollers_r);

  //turn left
  rotate_base(40, -123);

  //move front a bit
  move_base(40, 1.9);
  // move_base(50, 1);

  //SCORE!!!
  grab(false, 0.5);
  move_ramp(55);
  task::sleep(1000);
  move_base(40, -2);
}

void BigBot::move_base(double pow, velocityUnits vel) {
  aut.move_group_double(base_left, base_right, pow, vel);
}

void BigBot::move_base(double pow, float lim, velocityUnits vel, rotationUnits rot){
  aut.move_group_for(base_left, base_right, lim, rot, pow, vel);
}


void BigBot::rotate_base(double pow, velocityUnits vel) {
  pow = color_manage(default_color, pow);

  pow = gear_convert(pow);
  aut.move_group(base_left, pow, velocityUnits::pct);
  aut.move_group(base_right, -pow, velocityUnits::pct);
}

void BigBot::rotate_base(double pow, float lim, velocityUnits vel) {
  lim = color_manage(default_color, lim);

  pow = gear_convert(pow);
  // aut.mech_rotate(base_left, base_right, lim, rotationUnits::rev, pow, vel);//using encoders

  //using gyro
  // aut.mech_rotate_gyro(t.H, base_left, base_right, lim, pow, vel);
  aut.mech_rotate_dual_gyro(t.H, t.G, base_left, base_right, lim, pow, vel);

}

void BigBot::grab(bool intake, float revs) {
  if(!intake){
    revs = -revs;
  }
  aut.mech_rotate(rollers_l, rollers_r, revs, rotationUnits::rev, 100, velocityUnits::pct);
}

double BigBot::gear_convert(double input){
  return input * (5/3);
}

void BigBot::move_ramp(double speed, velocityUnits vel) {
  if(speed >= 0) { // move forward, stop with encoder

    aut.move_group_for(ramp_l, ramp_r, 5.8, rotationUnits::rev, speed, vel);
  } 
  else if(speed < 0) { // move backwards, stop with bumper
    // aut.move_group_for_bumper(bump_port, ramp_l, ramp_r, speed, vel);//not currently working
    aut.move_group_for(ramp_l, ramp_r, -5.8, rotationUnits::rev, speed, vel);
  } 
  // else { // hold lift
  //   aut.group_stop(ramp_l, ramp_r, brakeType::hold);
  // }
}

void BigBot::open_ramp(){
  //set on toque the base
  aut.activate_piston(Piston, false);
  //intake out
  aut.move_group(rollers_l,-100);
  aut.move_group(rollers_r,100);

  //piston for ramp
  aut.activate_piston(ramp_piston, true);
  task::sleep(1000);

  aut.activate_piston(ramp_piston, false);

  aut.group_stop(rollers_l, rollers_r);
}