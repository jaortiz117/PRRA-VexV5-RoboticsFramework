#include "movement.h"
#include "vex.h"


void driver::base_arcade(robot::MotorGroup& mg, vex::controller::axis axis_x,
                 vex::controller::axis axis_y) {
  // we assume that both sides of motor group have same amount of motors
  //left side 
  for (int i = 0; i < sizeof(mg.getLeft()); i++) {
    mg.getLeft()[i].spin(directionType::fwd, ((axis_y.value() + axis_x.value()) * 2),
                 velocityUnits::pct); //(y+x)/2;

    // right side
    mg.getRight()[i].spin(directionType::fwd, ((axis_y.value() - axis_x.value()) * 2),
                 velocityUnits::pct);
  }
  
}

void driver::mech(robot::MotorGroup& mg, vex::controller::axis axis){

  for (int i = 0; i < sizeof(mg.getLeft()); i++){
    //Left
    mg.getRight()[i].spin(directionType::fwd,  axis.value(), velocityUnits::pct);
   
    //Right
    mg.getLeft()[i].spin(directionType::rev,  axis.value(), velocityUnits::pct);
  }
}

void driver::mech(robot::MotorGroup& mg, vex::controller::button cw, vex::controller::button ccw){
    //assuming mg has same amount of motors on both sides
    
    if(cw.pressing()){
      for (int i = 0; i < sizeof(mg.getLeft()); i++){
        mg.getLeft()[i].spin(directionType::fwd, 100, velocityUnits::pct);
        mg.getRight()[i].spin(directionType::rev, 100, velocityUnits::pct);
      }
    }
    else if(ccw.pressing()){
      for (int i = 0; i < sizeof(mg.getLeft()); i++){
        mg.getLeft()[i].spin(directionType::rev, 100, velocityUnits::pct);
        mg.getRight()[i].spin(directionType::fwd, 100, velocityUnits::pct);
      }
    }
    else{
      for (int i = 0; i < sizeof(mg.getLeft()); i++){
        mg.getLeft()[i].stop(brakeType::brake);
        mg.getRight()[i].stop(brakeType::brake);
      }
    }
}

void driver::digi_out(robot::DigitalOutGroup& dg, vex::controller::button toggle){
  if(toggle.pressing()) {
    if(dg.get_single().value() == 1)
      dg.get_single().set( false );
    else
      dg.get_single().set( true );
  }
}

void driver::digi_out(robot::DigitalOutGroup &dg, vex::controller::button on,
              vex::controller::button off) {
  if (on.pressing()) {
    dg.get_single().set(true);
  } else if (off.pressing()) {
    dg.get_single().set(false);
  }
}