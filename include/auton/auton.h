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
    
  
    void move_group(vex::motor_group mg, double pow, vex::velocityUnits units);

    // autonomous movement of base indefinetely, speed sing dictates direction
    void move_group_double(vex::motor_group left_mg, vex::motor_group right_mg, double speed, velocityUnits vel_units = velocityUnits::pct);
    
    // Moves motor groups in the same direction using "rotateFor"
    void move_group_for(vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
    
    //moves motor group in same dir stopping on a switch
    void move_group_for_bumper(vex::triport::port &sensor_port, vex::motor_group left_mg, vex::motor_group right_mg, double speed, vex::velocityUnits vel_units);
    
    // Moves motor groups in separete directions, speed sing dictates direction
    void mech_rotate(vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
    
    //uses gyro to rotate
    void mech_rotate_gyro(vex::triport::port &sensor_port, vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
  
    // Stops motor groups, depending on brake type can be used for base or arm
    void group_stop(vex::motor_group left_mg, vex::motor_group right_mg, brakeType brake_type = brakeType::brake);

    // Moves piston
    void activate_piston(vex::digital_out dg, bool direction);
    
    // moves rollers and base simultaneously
    void score(vex::motor_group b_left, vex::motor_group b_right, vex::motor_group r_left, vex::motor_group r_right);
    
    // void digital_assign(robot::DigitalOutGroup dg, bool val);//on hold

    //TODO

  };
} // namespace auton

#endif
