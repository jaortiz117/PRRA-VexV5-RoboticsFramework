#ifndef DRIVER_H
#define DRIVER_H

#include "robot/robot.h"
#include "vex.h"

namespace driver {
void base_arcade(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::axis axis_x, vex::controller::axis axis_y);
void mech(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::axis axis);
void mech(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::button cw, vex::controller::button ccw);
void digi_out(vex::digital_out dg, vex::controller::button toggle);
void digi_out(vex::digital_out dg, vex::controller::button _on, vex::controller::button _off);
}

#endif