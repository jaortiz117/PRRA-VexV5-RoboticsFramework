#ifndef BIGBOT_H
#define BIGBOT_H

#include "robot.h"
#include "movement.h"
#include "util.h"
#include "vex.h"

//Whoever uses library only needs to make this file to create their robot instance (inheriting from robot class)
class BigBot : public robot::Bot{
  private:
  //default color
  util::Color default_color = util::Color::blue;

  //motors
  motor BaseLeft1 = motor(PORT5, ratio18_1, false);
  motor BaseLeft2 = motor(PORT12, ratio18_1, false);
  motor BaseLeft3 = motor(PORT15, ratio18_1, true);
  motor BaseRight1 = motor(PORT4, ratio18_1, true);
  motor BaseRight2 = motor(PORT9, ratio18_1, false);
  motor BaseRight3 = motor(PORT10, ratio18_1, true);
  motor RampL = motor(PORT14, ratio18_1, true);
  motor RampR = motor(PORT20, ratio18_1, false);
  motor RollerL1 = motor(PORT1, ratio18_1, true);
  motor RollerL2 = motor(PORT2, ratio18_1, true);
  motor RollerR1 = motor(PORT18, ratio18_1, true);
  motor RollerR2 = motor(PORT19, ratio18_1, true);

  //triports
  triport t = triport( PORT22 );
  triport::port bump_port = t.A;
  triport::port gyro_port = t.H;
  triport::port gyro_port2 = t.G;
  triport::port Piston = t.B;
  triport::port ramp_piston = t.C;
  // triport::port sonar_l = t.C;
  triport::port sonar_r = t.E;

  // digital_out ramp_piston = led(t.C);
  // bumper ramp_btn = bumper(t.A);
  // gyro g_sensor = gyro(t.H);

  vex::motor_group base_left= motor_group(BaseLeft1, BaseLeft2, BaseLeft3);
  vex::motor_group base_right= motor_group(BaseRight1, BaseRight2, BaseRight3);

  vex::motor_group ramp_l= motor_group(RampL);
  vex::motor_group ramp_r= motor_group(RampR);

  vex::motor_group rollers_l= motor_group(RollerL1, RollerL2);
  vex::motor_group rollers_r= motor_group(RollerR1, RollerR2);

  // vex::digital_out digi[1] = {Piston};
  // robot::DigitalOutGroup pist = robot::DigitalOutGroup(digi, digi);
  // robot::DigitalOutGroup piston_group = pist;

  auton::Auton aut = auton::Auton(pos, 4.0, 2.0, 7.0);

  public:
    BigBot(util::Position& _pos);
    void driver() override;
    void auton() override;
    void move_base(double pow, velocityUnits vel = velocityUnits::pct) override;
    void move_base(double pow, float lim, velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev) override;
    void rotate_base(double pow, velocityUnits vel = velocityUnits::pct) override;
    void rotate_base(double pow, float lim, velocityUnits vel = velocityUnits::pct) override;
    void grab(bool intake = true, float revs = 10.0) override;
    double gear_convert(double input);
    void move_ramp(double speed, velocityUnits vel = velocityUnits::pct);
    void open_ramp();
};

#endif