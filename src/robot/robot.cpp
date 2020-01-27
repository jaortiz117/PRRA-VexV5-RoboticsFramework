// #include "robot/robot.h"
// #include "util.h"
// #include "vex.h"

// template <class T>
// class robot::AbstractGroup{
//   public:
//     virtual T* getLeft() = 0;//return array of left side of group
//     virtual T* getRight() = 0;
// };

// class robot::MotorGroup : public robot::AbstractGroup<vex::motor>{
//   private:
//     vex::motor *left;
//     vex::motor *right;

//   public:
//     MotorGroup(vex::motor _left[], vex::motor _right[]){
//       left = _left;
//       right = _right;
//     }

//     vex::motor* getLeft(){
//       return left;
//     }

//     vex::motor* getRight(){
//       return right;
//     }
// };

// class robot::DigitalOutGroup : public robot::AbstractGroup<vex::digital_out>{
//   private:
//     vex::digital_out *left;
//     vex::digital_out *right;

//   public:
//     DigitalOutGroup(vex::digital_out _left[], vex::digital_out _right[]){
//       left = _left;
//       right = _right;
//     }

//     vex::digital_out* getLeft(){
//       return left;
//     }

//     vex::digital_out* getRight(){
//       return right;
//     }
// };


// class robot::ControllerGroup : public AbstractGroup<vex::controller>{
//   private:
//     vex::controller *left;
//     vex::controller *right;

//   public:
//     ControllerGroup(vex::controller _left[], vex::controller _right[]){
//       left = _left;
//       right = _right;
//     }

//     vex::controller* getLeft(){
//       return left;
//     }

//     vex::controller* getRight(){
//       return right;
//     }
// };

// class robot::Bot{
//   protected:
//     util::Position& pos;
//     robot::ControllerGroup& cg;
//   public:
//     Bot(util::Position& _pos, robot::ControllerGroup& _cg)
//       : pos{_pos}, cg{_cg}
//       {};
//     virtual void driver() = 0;
//     virtual void auton() = 0;
//     virtual void move_base(double power,
//            velocityUnits vel = velocityUnits::pct) = 0;
//     virtual void rotate_base(double power, velocityUnits vel = velocityUnits::pct) = 0;
//     virtual void grab(bool intake = true, float revs = 10.0) = 0;
// };