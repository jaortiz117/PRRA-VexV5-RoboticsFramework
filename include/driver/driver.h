#ifndef DRIVER_H
#define DRIVER_H

#include "robot/robot.h"
#include "vex.h"

namespace driver {
void base_arcade(robot::MotorGroup& mg, vex::controller::axis axis_x, vex::controller::axis axis_y);
void mech(robot::MotorGroup& mg, vex::controller::axis axis);
void mech(robot::MotorGroup& mg, vex::controller::button cw, vex::controller::button ccw);
void digi_out(robot::DigitalOutGroup& dg, vex::controller::button toggle);
void digi_out(robot::DigitalOutGroup& dg, vex::controller::button _on, vex::controller::button _off);
}

#endif