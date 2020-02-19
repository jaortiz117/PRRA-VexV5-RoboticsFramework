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
    float kp;
    float ki;
    float kd;
    float epsilon = 0.1;

    // unsigned int current_time, previous_time = vex::timer::system();
    // double elapsed_time;
    float error = 0.0;
    float last_error = 0.0;
    float cm_error= 0.0, rate_error = 0.0;

    public:
    PID(float _kp = 1.0, float _ki = 1.0, float _kd = 1.0) : 
    kp{_kp},ki{_ki},kd{_kd}{};

    float compute(float curr_val, float desired);
  };
}

#endif