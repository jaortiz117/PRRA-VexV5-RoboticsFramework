#ifndef PID_H
#define PID_H

#include "vex.h"

/*****************************
PID implementation (will be a class that is instantiated whenever a function uses PID)

https://www.teachmemicro.com/arduino-pid-control-tutorial/

This only needs to have something t return a 0 once the PID has been 
within acceptable range of desired val for x amount of time. So it returns a 0 once it ends

******************************/
namespace pid{
  class PID{
    private:
    double kp;
    double ki;
    double kd;
    double epsilon = 0.5;

    // unsigned int current_time, previous_time = vex::timer::system();
    // double elapsed_time;
    double error;
    double last_error = 0;
    double cm_error=0, rate_error;

    public:
    PID(double _kp, double _ki, double _kd) : 
    kp{_kp},ki{_ki},kd{_kd}{};

    double compute(double curr_val, double desired);
  };
}

#endif