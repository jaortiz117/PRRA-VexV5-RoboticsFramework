#include "pid.h"
#include "vex.h"

using namespace pid;

//adapted from https://www.teachmemicro.com/arduino-pid-control-tutorial/
float PID::compute(float curr_val, float desired){

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
  Brain.Screen.setCursor(4, 1);
  Brain.Screen.print("error: %4.2f cm_error: %4.2f rate_error: %4.2f", error, cm_error, rate_error);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("kp: %4.2f ki: %4.2f kd: %4.2f", kp, ki, kd);

  float out = kp * error + ki * cm_error + kd * rate_error; // PID output

  last_error = error;          // remember current error
  // previous_time = current_time; // remember current time
  Brain.Screen.setCursor(5, 1);
  Brain.Screen.print("curr_val: %4.2f", curr_val);
  Brain.Screen.setCursor(5, 10);
  Brain.Screen.print("desired: %4.2f", (float)desired);
  Brain.Screen.setCursor(5, 22);
  Brain.Screen.print("pre out: %4.2f", out);
  if(abs(curr_val - desired) < epsilon){
    return 0.0;
  }

  //control the limit
  if(out > 100.0) out = 100.0;
  if(out < -100.0) out = -100.0;

  Brain.Screen.setCursor(6, 22);
  Brain.Screen.print("post out: %4.2f", out);

  return out; // have function return the PID output
}