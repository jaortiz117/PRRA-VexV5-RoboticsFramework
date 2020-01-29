/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// BaseLeft1            motor         5               
// BaseLeft2            motor         12              
// BaseLeft3            motor         15              
// BaseRight1           motor         4               
// BaseRight2           motor         9               
// BaseRight3           motor         10              
// RampL                motor         14              
// RampR                motor         20              
// RollerL1             motor         1               
// RollerL2             motor         2               
// RollerR1             motor         18              
// RollerR2             motor         19              
// Piston               led           A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "util.h"
#include "robot/big_bot.h"

// #include "old_code.cpp"

using namespace vex;
using namespace util;
using namespace robot;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here


//Global instances of robot
Position POS = Position(Side::top, Color::red);
BigBot BIGGIE = BigBot(POS);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  

  //TODO here we can add display to choose and modify the position and later choose which robot is being driven
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  BIGGIE.auton();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

//temp
//  motor RampL = motor(PORT14, ratio18_1, false);
//   motor RampR = motor(PORT20, ratio18_1, false);

// class MotorGroup{
//   private:
//     vex::motor *left;
//     vex::motor *right;

//   public:
//     MotorGroup(vex::motor _left[], vex::motor _right[]) : 
//     left{_left}, right{_right}{}

//     vex::motor* getLeft();

//     vex::motor* getRight();
// };

// // MotorGroup
// vex::motor* MotorGroup::getLeft() { return left; }

// vex::motor* MotorGroup::getRight() { return right; }

// vex::motor ramp_l[1]= {RampL};
//   vex::motor ramp_r[1]= {RampR};
  // vex::motor_group ramp_gl= vex::motor_group(RampL);
  // vex::motor_group ramp_gr = vex::motor_group(RampR);

// void temp_mech(MotorGroup mg, vex::controller::axis axis){

//   for (int i = 0; i < arr_length(mg.getLeft()); i++){
//     //Left
//     mg.getRight()[i].spin(directionType::fwd,  axis.value(), velocityUnits::pct);
   
//     //Right
//     mg.getLeft()[i].spin(directionType::rev,  axis.value(), velocityUnits::pct);
//   }
// }

//^^ temp

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................


    BIGGIE.driver();
    // temp_mech(ramp_g, Controller1.Axis2);
    // for (int i = 0; i < arr_length(ramp_g.getLeft()); i++){
    //Left
    // ramp_gl.spin(directionType::fwd,  Controller1.Axis2.value(), velocityUnits::pct);
   
    // //Right
    // ramp_gr.spin(directionType::rev,  Controller1.Axis2.value(), velocityUnits::pct);
  // }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
