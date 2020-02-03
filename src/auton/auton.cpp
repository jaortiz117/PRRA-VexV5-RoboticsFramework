#include "movement.h"
#include "util.h"
#include "vex.h"

using namespace auton;


void Auton::move_group(vex::motor_group mg, double pow,
                      vex::velocityUnits units) {
  // assuming mg has same amount of motors on both sides
  // for (int i = 0; i < util::arr_length(mg.getRight()); i++) {
  //   mg.getRight()[i].spin(vex::directionType::rev, pow, units);
  // }

    mg.spin(directionType::fwd,  pow, units);

}

void Auton::move_group_double(vex::motor_group left_mg, vex::motor_group right_mg, double pow,
           velocityUnits vel){ // autonomous movement of base indefinetely
  move_group(left_mg, pow, vel);
  move_group(right_mg, pow, vel);
}
/*************************************
TODO these functions have been copy pasted from older projects,
they still  need to be translated into this library's design language
*************************************/

void Auton::move_group_for(vex::motor_group left_mg, vex::motor_group right_mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units){
// void motorRotateFor(vex::motor mL, vex::motor mR, float rotation, rotationUnits units, int speed, velocityUnits units_v){
    left_mg.resetRotation();
    right_mg.resetRotation();
    
    double dir = 1;
    if(lim < 0)
        dir  = -dir;
    
    lim = abs(lim);
   while((lim - abs((left_mg.rotation(rot_units) + right_mg.rotation(rot_units))/2)) == 0){
       //find encoder difference
       double dVel = abs(left_mg.velocity(vel_units)) - abs(right_mg.velocity(vel_units));
       
       //depending on which motor is slower substract the speed difference from faster motor
       if(dVel > 0){//mL faster
          //  moveBaseL(dir*(speed - dVel), units_v);
          //  moveBaseR(dir*speed, units_v);

           move_group(left_mg, dir*(speed - dVel), vel_units);
           move_group(right_mg, dir*speed, vel_units);
       }
       else if(dVel < 0){//mR faster
          //  moveBaseL(dir*speed, units_v);
          //  moveBaseR(dir*(speed - dVel), units_v);

           move_group(left_mg, dir*(speed - dVel), vel_units);
           move_group(left_mg, dir*speed, vel_units);
       }
       else{//speed is equal
          //  moveBaseL(dir*speed, units_v);
          //  moveBaseR(dir*speed, units_v);

           move_group(left_mg, dir*speed, vel_units);
           move_group(left_mg, dir*speed, vel_units);
       }
       
       task::sleep(5);
   }

   group_stop(left_mg, right_mg);
// }
}

// void Auton::mech_rotate(robot::MotorGroup mg, float lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units){//speed dictates if cw or ccw
// void rotateAlt(float revs, double speed){//+ is to cw, - to ccw
//     if(revs < 0){
//         speed = -speed;
//     }
//     //left
//     //moveBaseL(speed, velocityUnits::pct);
//     LMWheel.spin(directionType::fwd, speed, velocityUnits::pct);
//     LFWheel.spin(directionType::fwd, speed, velocityUnits::pct);
//     LBWheel.startRotateFor(revs, rotationUnits::rev, abs(speed), velocityUnits::pct);
    
//     Brain.Screen.printAt(1,40,"Encoder val: %f", RBWheel.rotation(rotationUnits::rev));
//     Brain.Screen.clearScreen();
    
//     //right
//     //cant use function becuase we need to use encoders
//     RMWheel.spin(directionType::fwd, -speed, velocityUnits::pct);
//     RFWheel.spin(directionType::fwd, -speed, velocityUnits::pct);
//     RBWheel.rotateFor(-revs, rotationUnits::rev, abs(speed), velocityUnits::pct);
    
//     baseStop(brakeType::brake);
// }
// }

//TODO define remaining methods from header file
//      Most of these methods can reuse the definitions from old_code.cpp
