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
  movement::mech(rollers_left, rollers_right, Controller1.ButtonR2, Controller1.ButtonR1);//rollers
  movement::digi_out(Piston, Controller1.ButtonUp, Controller1.ButtonDown);//transmission
}