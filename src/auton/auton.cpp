#include "movement.h"
#include "util.h"
#include "vex.h"
#include "pid.h"

using namespace auton;
using namespace pid;

void Auton::move_group(vex::motor_group mg, double pow,
                       vex::velocityUnits units) {
  // assuming mg has same amount of motors on both sides

  mg.spin(directionType::fwd, pow, units);
}

void Auton::move_group_double(
    vex::motor_group left_mg, vex::motor_group right_mg, double pow,
    velocityUnits vel, bool rotate) { // autonomous movement of base indefinetely
  move_group(left_mg, pow, vel);

  if(rotate) pow = -pow;
  move_group(right_mg, pow, vel);
}

//TODO make single motor_group function for this and turn this into a multithreaded function
void Auton::move_group_for(vex::motor_group left_mg, vex::motor_group right_mg,
                           double lim, vex::rotationUnits rot_units,
                           double speed, vex::velocityUnits vel_units) {
  // void motorRotateFor(vex::motor mL, vex::motor mR, float rotation,
  // rotationUnits units, int speed, velocityUnits units_v){
  left_mg.resetRotation();
  left_mg.resetPosition();
  right_mg.resetRotation();
  right_mg.resetPosition();

  double dir = 1;
  if (lim < 0)
    dir = -dir;

  lim = util::floating_abs(lim);

  Brain.Screen.setCursor(8, 1);
  Brain.Screen.print("aut.kp: %4.2f aut.ki: %4.2f aut.kd: %4.2f", kp, ki, kd);

  PID pid = PID(kp, ki, kd);
  float output = pid.compute(dir*(left_mg.rotation(rot_units) + right_mg.rotation(rot_units)) /2.0, (float)lim);
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print(output);
  while(output != 0.0){
  // while(lim - ((left_mg.rotation(rot_units) + right_mg.rotation(rot_units)) /2) > 0){
    double curr_speed = speed * (output/100);

    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(curr_speed);

    if(dir<0){
      curr_speed = -1 * util::floating_abs(curr_speed);
    }
    move_group_double(left_mg, right_mg, curr_speed, vel_units);
    output = pid.compute(dir*(left_mg.rotation(rot_units) + right_mg.rotation(rot_units)) /2, (float)lim);
    Brain.Screen.setCursor(2, 1);
    Brain.Screen.print(output);
  }

  // while (
  //     (lim - abs((left_mg.rotation(rot_units) + right_mg.rotation(rot_units)) /
  //                2)) >= 0) {
  //   // find encoder difference
  //   double dVel =
  //       abs(left_mg.velocity(vel_units)) - abs(right_mg.velocity(vel_units));

  //   // depending on which motor is slower substract the speed difference from
  //   // faster motor
  //   if (dVel > 0) { // mL faster
  //     //  moveBaseL(dir*(speed - dVel), units_v);
  //     //  moveBaseR(dir*speed, units_v);

  //     move_group(left_mg, dir * (speed - dVel), vel_units);
  //     move_group(right_mg, dir * speed, vel_units);
  //   } else if (dVel < 0) { // mR faster
  //     //  moveBaseL(dir*speed, units_v);
  //     //  moveBaseR(dir*(speed - dVel), units_v);

  //     move_group(left_mg, dir * (speed - dVel), vel_units);
  //     move_group(right_mg, dir * speed, vel_units);
  //   } else { // speed is equal
  //     //  moveBaseL(dir*speed, units_v);
  //     //  moveBaseR(dir*speed, units_v);

  //     move_group(left_mg, dir * speed, vel_units);
  //     move_group(right_mg, dir * speed, vel_units);
  //   }

  //   task::sleep(5);
  // }

  group_stop(left_mg, right_mg);
  // }
}

void Auton::move_group_for_bumper(vex::triport::port &sensor_port,
                                  vex::motor_group left_mg,
                                  vex::motor_group right_mg, double speed,
                                  vex::velocityUnits vel_units) {
  // int orig_val = bump.value();
  bumper bump = bumper(sensor_port);
  while (!bump.pressing()) {
    // while(1){
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(bump.value());

    move_group(left_mg, speed, vel_units);

    task::sleep(5);
  }

  group_stop(left_mg, right_mg);
}

// moves motor group in same dir stopping on a distance (sonar ports need to be
// connected one next to the other)
void Auton::move_group_for_sonar(vex::triport::port &sensor_port,
                                 vex::motor_group mg, double lim,
                                 vex::distanceUnits units, double speed,
                                 vex::velocityUnits vel_units) {
  vex::sonar sensor = vex::sonar(sensor_port);

  PID pid = PID(kp, ki, kd);
  double output = pid.compute(sensor.distance(units), lim);
  // double output = pid.compute(abs(sensor.distance(units) - lim), 0);
  Brain.Screen.clearScreen();
    // Brain.Screen.print(output);

  // while (output != 0) {
  while (util::floating_abs(sensor.distance(units) - lim) > 0) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(sensor.distance(units));

    // move_group(mg, dir*speed, vel_units);

    double curr_speed = speed * (output/100);
    // Brain.Screen.print(output);
    move_group(mg, curr_speed, vel_units);
    output = pid.compute(sensor.distance(units), lim);
    // output = pid.compute(abs(sensor.distance(units) - lim), 0);

    this_thread::sleep_for(15);
  }

  group_stop(mg, mg);
}

// moves motor group in same dir stopping on a distance (sonar ports need to be
// connected one next to the other)
void Auton::move_group_for_sonar(vex::triport::port &sensor_port,
                                 vex::motor_group left_mg,
                                 vex::motor_group right_mg, int dir, double lim,
                                 vex::distanceUnits units, double speed,
                                 vex::velocityUnits vel_units) {
  vex::sonar sensor = vex::sonar(sensor_port);

  while (util::floating_abs(sensor.distance(units) - lim) > 0) {
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print(sensor.distance(units));

    move_group(left_mg, dir*speed, vel_units);
    move_group(right_mg, dir*speed, vel_units);

    this_thread::sleep_for(5);
  }

  group_stop(left_mg, right_mg);
}

// moves motor group in same dir stopping on a distance (sonar ports need to be
// connected one next to the other)
void Auton::move_group_for_dual_sonar(vex::triport::port &sensor_port,
                                      vex::triport::port &sensor_port_2,
                                      vex::motor_group left_mg,
                                      vex::motor_group right_mg, double lim,
                                      vex::distanceUnits units, double speed,
                                      vex::velocityUnits vel_units) {

  // thread's callback function cannot have any parameters
  // a capturing lambda cannot convert to void type
  // a non capturing lambda can convert to void type
  // The gist of the trick is passing the lambda function as the callback
  // argument and providing a captureless thunk as the callback function pointer

  auto left = [this, &sensor_port, left_mg, lim, units, speed, vel_units]() {
    move_group_for_sonar(sensor_port, left_mg, lim, units, speed, vel_units);
  };
  auto left_thunk = [](void *arg) { // note thunk is captureless
    (*static_cast<decltype(left) *>(arg))();
  };

  auto right = [this, &sensor_port_2, right_mg, lim, units, speed,
                vel_units]() {
    move_group_for_sonar(sensor_port_2, right_mg, lim, units, speed, vel_units);
  };
  auto right_thunk = [](void *arg) { // note thunk is captureless
    (*static_cast<decltype(right) *>(arg))();
  };

  // start threads
  vex::thread t(left_thunk, &left);
  vex::thread t_R(right_thunk, &right);
}

// Moves motor groups in separete directions, sing dictates direction
void Auton::mech_rotate(vex::motor_group left_mg, vex::motor_group right_mg, double lim, vex::rotationUnits rot_units, double speed, vex::velocityUnits vel_units) { 
//   left_mg.resetRotation();
// right_mg.resetRotation();
//   if(lim < 0){
//     speed = -speed;
// }
  left_mg.rotateFor(lim, rot_units, abs(speed), vel_units, false); //to change direction, change sign of lim

  right_mg.rotateFor(-lim, rot_units, abs(speed), vel_units);

  group_stop(left_mg, right_mg);
}

void Auton::mech_rotate_gyro(vex::triport::port &sensor_port, vex::motor_group left_mg, vex::motor_group right_mg, double deg, double speed, vex::velocityUnits vel_units) {
  gyro sensor = gyro(sensor_port);
  util::gyro_calibrate(sensor);
  task::sleep(200); // jic
  sensor.resetHeading();
  // sensor.setHeading(0.0, rot_units);

  if (deg < 0) { // ccw
    deg = 360 + deg;
    sensor.setHeading(359.0, rotationUnits::deg);

    while (sensor.heading(rotationUnits::deg) >= deg) {
      move_group(left_mg, -speed, vel_units);
      move_group(right_mg, speed, vel_units);

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(sensor.heading(rotationUnits::deg));

      task::sleep(5);
    }
  } else { // cw
    // if(rot_units == rotationUnits::deg) sensor.setHeading(359.0, rot_units);
    while (sensor.heading(rotationUnits::deg) <= deg) {
      move_group(left_mg, speed, vel_units);
      move_group(right_mg, -speed, vel_units);

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(sensor.heading(rotationUnits::deg));

      task::sleep(5);
    }
  }

  group_stop(left_mg, right_mg, brakeType::hold);
}

void Auton::mech_rotate_dual_gyro(vex::triport::port &sensor_port,vex::triport::port &sensor_port_2,
                             vex::motor_group left_mg,
                             vex::motor_group right_mg, double deg,
                             double speed, vex::velocityUnits vel_units) {

  gyro sensor = gyro(sensor_port);
  gyro sensor_2 = gyro(sensor_port_2);
  util::gyro_calibrate(sensor);
  util::gyro_calibrate(sensor_2);
  task::sleep(200); // jic
  sensor.resetHeading();
  sensor_2.resetHeading();
  // sensor.setHeading(0.0, rot_units);

  if (deg < 0) { // ccw
    //temporarily disabled
    //deg = 360 + deg;
    sensor.setHeading(359.0, rotationUnits::deg);
    sensor_2.setHeading(359.0, rotationUnits::deg);

    //temp------------------
    deg = ((sensor.heading(rotationUnits::deg) + sensor_2.heading(rotationUnits::deg))/2) + deg;//its a negative num so we add
    //temp------------------

    while ((sensor.heading(rotationUnits::deg) + sensor_2.heading(rotationUnits::deg))/2 >= deg) {
      move_group(left_mg, -speed, vel_units);
      move_group(right_mg, speed, vel_units);

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(sensor.heading(rotationUnits::deg));
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(sensor_2.heading(rotationUnits::deg));

      task::sleep(5);
    }
  } else { // cw
    // if(rot_units == rotationUnits::deg) sensor.setHeading(359.0, rot_units);
    //temp------------------
    deg = ((sensor.heading(rotationUnits::deg) + sensor_2.heading(rotationUnits::deg))/2) + deg;
    //temp------------------
    while ((sensor.heading(rotationUnits::deg) + sensor_2.heading(rotationUnits::deg))/2 <= deg) {
      move_group(left_mg, speed, vel_units);
      move_group(right_mg, -speed, vel_units);

      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(sensor.heading(rotationUnits::deg));
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(sensor_2.heading(rotationUnits::deg));

      task::sleep(5);
    }
  }

  group_stop(left_mg, right_mg, brakeType::hold);
}

// Stops motor groups, depending on brake type can be used for base or arm
void Auton::group_stop(vex::motor_group left_mg, vex::motor_group right_mg, brakeType brake_type) {
  left_mg.stop(brake_type);
  right_mg.stop(brake_type);
}

void Auton::activate_piston(vex::triport::port &tp, bool direction) {
    digital_out dg = led(tp);
    dg.set(direction);
}
