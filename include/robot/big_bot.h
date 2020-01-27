#ifndef BIGBOT_H
#define BIGBOT_H

#include "robot.h"

class BigBot : public robot::Bot{
  private:
    robot::MotorGroup *base_group;
    robot::MotorGroup *ramp_group;
    robot::MotorGroup *rollers_group;
    robot::DigitalOutGroup *piston_group;
  public:
    BigBot(util::Position& _pos, robot::ControllerGroup& _cg);
    void driver() override;
    void auton() override;
    void move_base(double power,
           velocityUnits vel = velocityUnits::pct) override;
    void rotate_base(double power, velocityUnits vel = velocityUnits::pct) override;
    void grab(bool intake = true, float revs = 10.0) override;
};

#endif