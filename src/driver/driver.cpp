#include "movement.h"
#include "util.h"
#include "vex.h"


void driver::base_arcade(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::axis axis_x,
                 vex::controller::axis axis_y) {
  // we assume that both sides of motor group have same amount of motors
  //left side 
  // for (int i = 0; i < util::arr_length(mg.getLeft()); i++) {
  //   mg.getLeft()[i].spin(directionType::fwd, ((axis_y.value() + axis_x.value()) * 2),
  //                velocityUnits::pct); //(y+x)/2;

  //   // right side
  //   mg.getRight()[i].spin(directionType::fwd, ((axis_y.value() - axis_x.value()) * 2),
  //                velocityUnits::pct);
  // }
  // Brain.Screen.print(axis_x.value());

  //Left
  left_mg.spin(directionType::fwd, ((axis_y.value() + axis_x.value()) * 2), velocityUnits::pct);
   
  //Right
  right_mg.spin(directionType::fwd, ((axis_y.value() - axis_x.value()) * 2), velocityUnits::pct);
  
}

void driver::mech(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::axis axis){

  // for (int i = 0; i < util::arr_length(mg.getLeft()); i++){
  //   //Left
  //   mg.getRight()[i].spin(directionType::fwd,  axis.value(), velocityUnits::pct);
   
  //   //Right
  //   mg.getLeft()[i].spin(directionType::rev,  axis.value(), velocityUnits::pct);
  // }

  //Left
  left_mg.spin(directionType::fwd,  Controller1.Axis2.value(), velocityUnits::pct);
   
  //Right
  right_mg.spin(directionType::fwd,  Controller1.Axis2.value(), velocityUnits::pct);
}

void driver::mech(vex::motor_group left_mg, vex::motor_group right_mg, vex::controller::button cw, vex::controller::button ccw){
  //assuming mg has same amount of motors on both sides
    
  if(cw.pressing()){
    left_mg.spin(directionType::fwd,  100, velocityUnits::pct);
    right_mg.spin(directionType::rev,  100, velocityUnits::pct);
  }
  else if(ccw.pressing()){
    left_mg.spin(directionType::rev,  100, velocityUnits::pct);
    right_mg.spin(directionType::fwd,  100, velocityUnits::pct);
  }
  else{
    left_mg.stop(brakeType::brake);
    right_mg.stop(brakeType::brake);
  }
}

void driver::mech(vex::motor_group mg, vex::controller::button cw, vex::controller::button ccw){
    if(cw.pressing()){
      mg.spin(directionType::fwd,  100, velocityUnits::pct);
    }
    else if(ccw.pressing()){
      mg.spin(directionType::rev,  100, velocityUnits::pct);
    }
    else{
      mg.stop(brakeType::brake);
    }
}

void driver::digi_out(vex::digital_out dg, vex::controller::button toggle){
  if(toggle.pressing()) {
    if(dg.value() == 1)
      dg.set( false );
    else
      dg.set( true );
  }
}

void driver::digi_out(vex::digital_out dg, vex::controller::button _on,
              vex::controller::button _off) {
  if (_on.pressing()) {
    dg.set(true);
  } else if (_off.pressing()) {
    dg.set(false);
  }
}