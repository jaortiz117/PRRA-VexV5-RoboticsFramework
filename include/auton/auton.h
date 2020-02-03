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
    void move_group_double(vex::motor_group left_mg, vex::motor_group right_mg, double speed, velocityUnits vel_units = velocityUnits::pct){
      left_mg.spin(fwd, speed, vel_units);
      right_mg.spin(fwd, speed, vel_units);
    }
    
    // Moves motor groups in the same direction using "rotateFor"
    void move_group_for(vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units) {
      left_mg.rotateFor(fwd, lim, rot_units, speed, vel_units); 
      right_mg.rotateFor(fwd, lim, rot_units, speed, vel_units);
    }
    
    // Moves motor groups in separete directions, speed sing dictates direction
    void mech_rotate(vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units) { 
      left_mg.rotateFor(fwd, lim, rot_units, -speed, vel_units); //to change direction, change sing of input speed
      right_mg.rotateFor(fwd, lim, rot_units, speed, vel_units);
    }
  
    // Stops motor groups, depending on brake type can be used for base or arm
    void stop_group(vex::motor_group left_mg, vex::motor_group right_mg, brakeType brake_type = brakeType::brake) {
      left_mg.stop(brake_type);
      right_mg.stop(brake_type);
    }
    
    
    // void mech_ccw(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units);
    // void digital_assign(robot::DigitalOutGroup dg, bool val);//on hold

    //TODO

  };
} // namespace auton

#endif
