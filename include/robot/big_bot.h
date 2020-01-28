#ifndef BIGBOT_H
#define BIGBOT_H

#include "robot.h"

//Whoever uses library only needs to make this file to create their robot instance (inheriting from robot class)
class BigBot : public robot::Bot{
  private:

  motor BaseLeft1 = motor(PORT5, ratio18_1, false);
  motor BaseLeft2 = motor(PORT12, ratio18_1, false);
  motor BaseLeft3 = motor(PORT15, ratio18_1, false);
  motor BaseRight1 = motor(PORT4, ratio18_1, false);
  motor BaseRight2 = motor(PORT9, ratio18_1, false);
  motor BaseRight3 = motor(PORT10, ratio18_1, false);
  motor RampL = motor(PORT14, ratio18_1, false);
  motor RampR = motor(PORT20, ratio18_1, false);
  motor RollerL1 = motor(PORT1, ratio18_1, false);
  motor RollerL2 = motor(PORT2, ratio18_1, false);
  motor RollerR1 = motor(PORT18, ratio18_1, false);
  motor RollerR2 = motor(PORT19, ratio18_1, false);
  // led Piston = led(Brain.ThreeWirePort.A);
  triport t = triport( PORT22 );
  digital_out Piston = led(t.A);

  vex::motor base_left[3]= {BaseLeft1, BaseLeft2, BaseLeft3};
  vex::motor base_right[3]= {BaseRight1, BaseRight2, BaseRight3};
  robot::MotorGroup base = robot::MotorGroup(base_left, base_right);
  robot::MotorGroup base_group = base;

  vex::motor ramp_l[1]= {RampL};
  vex::motor ramp_r[1]= {RampR};
  robot::MotorGroup ramp = robot::MotorGroup(ramp_l, ramp_r);
  robot::MotorGroup ramp_group = ramp;

  vex::motor rollers_l[2]= {RollerL1, RollerL2};
  vex::motor rollers_r[2]= {RollerR1, RollerR2};
  robot::MotorGroup roll = robot::MotorGroup(rollers_l, rollers_r);
  robot::MotorGroup rollers_group = roll;

  vex::digital_out digi[1] = {Piston};
  robot::DigitalOutGroup pist = robot::DigitalOutGroup(digi, digi);
  robot::DigitalOutGroup piston_group = pist;

  public:
    BigBot(util::Position& _pos, robot::ControllerGroup& _cg);
    void driver() override;
    void auton() override;
    void move_base(double pow,
           velocityUnits vel = velocityUnits::pct) override;
    void rotate_base(double pow, velocityUnits vel = velocityUnits::pct) override;
    void grab(bool intake = true, float revs = 10.0) override;
};

#endif