#include "pid.h"
#include "vex.h"

using namespace pid;

//adapted from https://www.teachmemicro.com/arduino-pid-control-tutorial/
double PID::compute(double curr_val, double desired){

  //this will continualy output a value. 
  //We need to use epsilon to have it output 0 if within epsilon
  // current_time = vex::timer::system(); // get current time
  // elapsed_time =
  //     (double)(current_time -
  //              previous_time); // compute time elapsed from previous computation

  error = desired - curr_val;                        // determine error
  cm_error += error;               // compute integral
  // cm_error += error * elapsed_time;               // compute integral
  rate_error = (error - last_error); // compute derivative
  // rate_error = (error - last_error) / elapsed_time; // compute derivative

  double out = kp * error + ki * cm_error + kd * rate_error; // PID output

  last_error = error;          // remember current error
  // previous_time = current_time; // remember current time

  if(abs(curr_val - desired) < epsilon){
    return 0;
  }

  //control the limit
  if(out > 100) out = 100;
  if(out < -100) out = -100;

  return out; // have function return the PID output
}