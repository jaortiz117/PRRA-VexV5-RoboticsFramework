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
  void move_group_for(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);//motors will move in same direction
  void mech_rotate(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);//speed dictates if cw or ccw
  // void mech_ccw(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
  void group_stop(robot::MotorGroup mg, brakeType brake = brakeType::brake);//stops mg
  void digital_assign(robot::DigitalOutGroup dg, bool value);
};
} // namespace auton

#endif