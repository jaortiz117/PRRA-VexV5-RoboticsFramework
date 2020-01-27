#ifndef AUTON_H
#define AUTON_H

#include "robot/robot.h"
#include "util.h"

namespace auton {
class Auton {
private:
    util::Position& pos;
  public:
    Auton(util::Position& _pos)
      : pos{_pos}{

    };
  util::Position& get_pos(){
    return pos;
  };
  void move_group_L(robot::MotorGroup mg, double power, vex::velocityUnits units);
  void move_group_R(robot::MotorGroup mg, double power, vex::velocityUnits units);
  void move_group(robot::MotorGroup mg, double power,
           velocityUnits vel = velocityUnits::pct); // autonomous movement of base indefinetely
  void mech_cw(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
  void mech_ccw(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
  void digital_assign(robot::DigitalOutGroup dg, bool value);
};
} // namespace auton

#endif