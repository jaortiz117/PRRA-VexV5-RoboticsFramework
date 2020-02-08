#ifndef SMALLBOT_H
#define SMALLBOT_H

#include "robot/robot.h"
#include "movement.h"
#include "vex.h"

class SmallBot : public robot::Bot{
  private:

    //TODO Configure rotation-------------------------------------------------------------------------
  motor BaseLeft1 = motor(PORT3, ratio18_1, false);
  motor BaseLeft2 = motor(PORT4, ratio18_1, false);
  motor BaseRight1 = motor(PORT1, ratio18_1, false);
  motor BaseRight2 = motor(PORT2, ratio18_1, false);
  motor LiftLeft = motor(PORT10, ratio18_1, false);
  motor LiftRight = motor(PORT9, ratio18_1, false);
  motor Ramp = motor(PORT6, ratio18_1, false);
  motor RollersLeft = motor(PORT8, ratio18_1, false);
  motor RollersRight = motor(PORT7, ratio18_1, false);

  vex::motor_group base_left = motor_group(BaseLeft1, BaseRight2);
  vex::motor_group base_right = motor_group(BaseRight1, BaseRight2);

  vex::motor_group lift_left = motor_group(LiftLeft);
  vex::motor_group lift_right = motor_group(LiftRight);

  vex::motor_group ramp = motor_group(Ramp);

  vex::motor_group rollers_left = motor_group(RollersLeft);
  vex::motor_group rollers_right = motor_group(RollersRight);

  //TODO Comfigure piston ----------------------------------------------------------------------------
  triport t = triport(PORT22);
  digital_out Piston = led(t.B);
  
  auton::Auton aut = auton::Auton(pos);

  public:
    SmallBot(util::Position& _pos);
    void driver() override;
    void auton() override;
    void move_base(double pow, velocityUnits vel = velocityUnits::pct) override;
    void move_base(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev) override;
    void rotate_base(double pow, velocityUnits vel = velocityUnits::pct) override;
    void rotate_base(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev) override;
    void move_lift(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev);
    void grab(bool intake = true, float revs = 10.0) override;
    double gear_convert(double input);
};

#endif