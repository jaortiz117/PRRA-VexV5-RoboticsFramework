#include "pid.h"
#include "vex.h"

using namespace pid;

//adapted from https://www.teachmemicro.com/arduino-pid-control-tutorial/
double PID::compute(double curr_val, double desired){

  //TODO this will continualy output a value. 
  //We need to use epsilon to have it output 0 if within epsilon
  current_time = vex::timer::system(); // get current time
  elapsed_time =
      (double)(current_time -
               previous_time); // compute time elapsed from previous computation

  error = desired - curr_val;                        // determine error
  cm_error += error * elapsed_time;               // compute integral
  rate_error = (error - last_error) / elapsed_time; // compute derivative

  double out = kp * error + ki * cm_error + kd * rate_error; // PID output

  last_error = error;          // remember current error
  previous_time = current_time; // remember current time

  return out; // have function return the PID output
}