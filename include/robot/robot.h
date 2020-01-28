#ifndef ROBOT_H
#define ROBOT_H

#include "../util.h"
#include "vex.h"

namespace robot {
template <class T>
class AbstractGroup{
  public:
    virtual T* getLeft() ;//return array of left side of group
    virtual T* getRight() ;
};

class MotorGroup : public AbstractGroup<vex::motor>{
  private:
    vex::motor *left;
    vex::motor *right;

  public:
    MotorGroup(vex::motor _left[], vex::motor _right[]) : 
    left{_left}, right{_right}{
      // left = _left;
      // right = _right;
    }

    vex::motor* getLeft(){
      return left;
    }

    vex::motor* getRight(){
      return right;
    }
};
// class DigitalOutGroup;
// class ControllerGroup;

class DigitalOutGroup : public AbstractGroup<vex::digital_out>{
  private:
    vex::digital_out *left;
    vex::digital_out *right;

  public:
    DigitalOutGroup(vex::digital_out _left[], vex::digital_out _right[]) : 
    left{_left}, right{_right}{
      // left = _left;
      // right = _right;
    }

    vex::digital_out* getLeft(){
      return left;
    }

    vex::digital_out* getRight(){
      return right;
    }

    vex::digital_out get_single(){
      return left[0];
    }
};


class ControllerGroup : public AbstractGroup<vex::controller>{
  private:
    vex::controller *controllers;

  public:
    ControllerGroup(vex::controller _controllers[]) : controllers{_controllers}{
      // controllers = _controllers;
    }

    vex::controller* getLeft(){
      return controllers;
    }

    vex::controller* getRight(){
      return controllers;
    }

    vex::controller* get_all(){
      return controllers;
    }

    vex::controller get_first(){
      return controllers[0];
    }
};

// class Bot;
class Bot{
  protected:
    util::Position& pos;
    robot::ControllerGroup& cg;
  public:
    Bot(util::Position& _pos, robot::ControllerGroup& _cg)
      : pos{_pos}, cg{_cg}
      {};
    virtual void driver();
    virtual void auton();
    virtual void move_base(double pow,
           velocityUnits vel = velocityUnits::pct);
    virtual void rotate_base(double pow, velocityUnits vel = velocityUnits::pct);
    virtual void grab(bool intake = true, float revs = 10.0);
};
}

#endif