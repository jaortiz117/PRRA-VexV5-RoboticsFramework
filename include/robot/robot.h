#ifndef ROBOT_H
#define ROBOT_H

#include "../util.h"
#include "vex.h"

namespace robot {
// class AbstractGroup{
//   public:
//     virtual T* getLeft() ;//return array of left side of group
//     virtual T* getRight() ;
// };

// class MotorGroup : public AbstractGroup<vex::motor>{
//   private:
//     vex::motor *left;
//     vex::motor *right;

//   public:
//     MotorGroup(vex::motor _left[], vex::motor _right[]) :
//     left{_left}, right{_right}{
//       // left   = _left;
//       // right = _right;
//     }

//     vex::motor* getLeft();

//     vex::motor* getRight();
// };
// // class DigitalOutGroup;
// // class ControllerGroup;

// class DigitalOutGroup : public AbstractGroup<vex::digital_out>{
//   private:
//     vex::digital_out *left;
//     vex::digital_out *right;

//   public:
//     DigitalOutGroup(vex::digital_out _left[], vex::digital_out _right[]) :
//     left{_left}, right{_right}{
//       // left = _left;
//       // right = _right;
//     }

//     vex::digital_out* getLeft();

//     vex::digital_out* getRight();

//     vex::digital_out get_single();
// };

// class ControllerGroup : public AbstractGroup<vex::controller>{
//   private:
//     vex::controller *controllers;

//   public:
//     ControllerGroup(vex::controller _controllers[]) :
//     controllers{_controllers}{
//       // controllers = _controllers;
//     }

//     vex::controller* getLeft();

//     vex::controller* getRight();

//     vex::controller* get_all();

//     vex::controller get_first();
// };

// class Bot;
class Bot {
protected:
  util::Position &pos;

public:
  Bot(util::Position &_pos) : pos{_pos} {};
  virtual void driver();
  virtual void auton();
  virtual void move_base(double pow, velocityUnits vel = velocityUnits::pct);
  virtual void move_base(double pow, float lim,
           velocityUnits vel = velocityUnits::pct, rotationUnits rot = rotationUnits::rev);
  virtual void rotate_base(double pow, velocityUnits vel = velocityUnits::pct);
  virtual void rotate_base(double pow, float lim, velocityUnits vel = velocityUnits::pct);
  virtual void grab(bool intake = true, float revs = 10.0);
};
} // namespace robot

#endif