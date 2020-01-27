#include "movement.h"
#include "vex.h"

using namespace auton;

void Auton::move_group_L(robot::MotorGroup mg, double power,
                      vex::velocityUnits units) {
  // assuming mg has same amount of motors on both sides
  for (int i = 0; i < sizeof(mg.getLeft()); i++) {
    mg.getLeft()[i].spin(vex::directionType::fwd, power, units);
  }
}

void Auton::move_group_R(robot::MotorGroup mg, double power,
                      vex::velocityUnits units) {
  // assuming mg has same amount of motors on both sides
  for (int i = 0; i < sizeof(mg.getLeft()); i++) {
    mg.getRight()[i].spin(vex::directionType::rev, power, units);
  }
}

//TODO define remaining methods from header file
//      Most of these methods can reuse the definitions from old_code.cpp
