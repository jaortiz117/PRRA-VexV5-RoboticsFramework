#include "vex.h"
#include "robot-config.h"

//TODO
// Make class to initialize all parameters for driver Control
// should contain methods for arcade and any necessary movement on the Controller
// Its parameters should be motor arrays for each section (base, lift, mech)

//vex::competition Competition;

vex::motor29 Pivot29(Brain.ThreeWirePort.A);
vex::motor29 Claw29(Brain.ThreeWirePort.C);
vex::line Detector(Brain.ThreeWirePort.B);
vex::motor29 Grabber29(Brain.ThreeWirePort.D);

digital_out dig1 = digital_out( Brain.ThreeWirePort.H );

/**********
Constants
**********/
const float MAXSPEED = 100;//NUMBER BETWEEN 0 AND 100. speed of flywheel

/**********
Globals
**********/
bool redSide = false;
bool blueSide = false;
bool programming = false;

/**********
Helper functions
Note: the ones we need to reuse are not commented, legacy functions are commented out
**********/
// void start();//starts flywheel
// void startSS(int speed);
// void stop();//stops flywheel
void dualButtonMovement(vex::controller::button cwBtn, vex::controller::button ccwBtn, vex::motor m);
void dualButtonMovement29(vex::controller::button cwBtn, vex::controller::button ccwBtn, vex::motor29 m);
// bool flyIsSpinning();
// bool flyIsMaxed();
bool ballDetected();// may be useful for detecting things with line sensors
//this function takes in 2 encoded motors but spins both sides of the base
void motorRotateFor(vex::motor mL, vex::motor mR, float rotation, rotationUnits units = rotationUnits::rev, int speed = 100, velocityUnits units_v = velocityUnits::pct);

/**********
Movement functions
**********/
void arcade(vex::controller::axis yAxis, vex::controller::axis xAxis);//arcade base
void grabber(vex::controller::button inBtn, vex::controller::button outBtn);//intake
// void lifter(vex::controller::button upBtn, vex::controller::button downBtn);//back ball lifter
void lift(vex::controller::axis axis);//Cap remover lift arm
// void flywheel(vex::controller::button stBtn, vex::controller::button stpBtn);//back flywheel
void pistones(vex::controller::button openBtn, vex::controller::button closeBtn);//pistones duh

/**********
Autonomous functions
**********/
void moveBaseL(double power, velocityUnits vel);//moves left side of base indefinetely
void moveBaseR(double power, velocityUnits vel);//moves right side of base indefinetely
void moveBase(double power, velocityUnits vel = velocityUnits::pct);//autonomous movement of base indefinetely
void rotateBase(double power, velocityUnits vel = velocityUnits::pct);//rotates base indefinetely
void grab(bool intake=true);//intake 10 revs
void rotateAlt(float revs, double speed = 50.0);//rotates up to point
void baseStop(brakeType brake = brakeType::brake);//stops base
void move(float Distance, double speed = 100.0);//moves base front
void moveBack(float Distance, double speed = 100.0);//moves base back
void intake(float revs, bool intake = true);//intake, u set up revs
// void launch(float revs, int flySpeed = MAXSPEED);//launches ball

// /**********
// Pre autonomous
// **********/
// void pre_auton(){
    
// }

/**********
Autonomous
// **********/
// void auton(){   
//     /***
//     currently on blue side
//     */ 
      
//      if(blueSide){
   
//      }
    
    
//     else if(programming){//Programing
        
    
//     }
    
//     else if(redSide){/***/
//     //ROJO
    
    
//     }
    
// }

/**********
Driver Control
**********/
// void driver() {

//     while(true){
//         /**********
//         Arcade
//         **********/
//         //arcade(Controller1.Axis2, Controller1.Axis1);
//         arcade(Controller1.Axis3, Controller1.Axis4);
        
//         /**********
//         Grabber
//         **********/
//         grabber(Controller1.ButtonL1, Controller1.ButtonL2);
        
//         /**********
//         Lifter
//         **********/
//         lifter(Controller1.ButtonR2, Controller1.ButtonR1);
        
//         /********
//         FlyWheel
//         *********/        
//         flywheel(Controller1.ButtonA, Controller1.ButtonB);
        
//         /*********
//         Lifter
//         **********/
//         lift(Controller1.Axis2);
        
//         /**********
//         pistones
//         **********/
//         pistones(Controller1.ButtonUp, Controller1.ButtonLeft);
        
//         task::sleep(20);
//     }
    
// }

// /**********
// Main
// **********/
// int main(){
//      //Run the pre-autonomous function. 
//     pre_auton();
    
//     //Set up callbacks for autonomous and driver control periods.
//     Competition.autonomous( auton );
//     Competition.drivercontrol( driver );

//     //Prevent main from exiting with an infinite loop.                        
//     while(1) {
//       vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
//     } 
// }

/**********
Helper Functions
**********/

// void start(){    
//     RFly.spin(directionType::fwd, MAXSPEED, velocityUnits::pct);
//     LFly.spin(directionType::fwd, MAXSPEED, velocityUnits::pct); 
// }

// void startSS(int speed){
//     RFly.spin(directionType::fwd, speed, velocityUnits::pct);
//     LFly.spin(directionType::fwd, speed, velocityUnits::pct); 
// }

// void stop(){
//     RFly.stop(brakeType::coast);
//     LFly.stop(brakeType::coast);
// }

void dualButtonMovement(vex::controller::button cwBtn, vex::controller::button ccwBtn, vex::motor m){
    if(cwBtn.pressing())
        m.spin(directionType::fwd, 100, velocityUnits::pct);
    else if(ccwBtn.pressing())
        m.spin(directionType::rev, 100, velocityUnits::pct);
    else
        m.stop(brakeType::brake);
}

void dualButtonMovement29(vex::controller::button cwBtn, vex::controller::button ccwBtn, vex::motor29 m){
    if(cwBtn.pressing())
        m.spin(directionType::fwd, 100, velocityUnits::pct);
    else if(ccwBtn.pressing())
        m.spin(directionType::rev, 100, velocityUnits::pct);
    else
        m.stop();
}

// bool flyIsSpinning(){
//     return LFly.velocity(velocityUnits::pct) != 0.0 && RFly.velocity(velocityUnits::pct) != 0.0;
// }

// bool flyIsMaxed(){
//     double pError = 6.0;
//     return LFly.velocity(velocityUnits::pct) >= (MAXSPEED - pError) && RFly.velocity(velocityUnits::pct) >= (MAXSPEED - pError);
// }

bool ballDetected(){
    //return Detector.value(analogUnits::pct) <= 68;//TODO make a const or global for framework
    return true;//sensor not connected yet
}

void motorRotateFor(vex::motor mL, vex::motor mR, float rotation, rotationUnits units, int speed, velocityUnits units_v){
    mL.resetRotation();
    mR.resetRotation();
    
    double dir = 1;
    if(rotation < 0)
        dir  = -dir;
    
    rotation = abs(rotation);
   while((rotation - abs((mL.rotation(units) + mR.rotation(units))/2)) == 0){
       //find encoder difference
       double dVel = abs(mL.velocity(units_v)) - abs(mR.velocity(units_v));
       
       //depending on which motor is slower substract the speed difference from faster motor
       if(dVel > 0){//mL faster
           moveBaseL(dir*(speed - dVel), units_v);
           moveBaseR(dir*speed, units_v);
       }
       else if(dVel < 0){//mR faster
           moveBaseL(dir*speed, units_v);
           moveBaseR(dir*(speed - dVel), units_v);
       }
       else{//speed is equal
           moveBaseL(dir*speed, units_v);
           moveBaseR(dir*speed, units_v);
       }
       
       task::sleep(5);
   }
}

/**********
Movement Functions
**********/
// TODO
// void arcade(vex::controller::axis yAxis, vex::controller::axis xAxis){
//     //left side
//     LFWheel.spin(directionType::fwd, ((yAxis.value() + xAxis.value())*2), velocityUnits::pct); //(y+x)/2;
//     LMWheel.spin(directionType::fwd, ((yAxis.value() + xAxis.value())*2), velocityUnits::pct);
//     LBWheel.spin(directionType::fwd, ((yAxis.value() + xAxis.value())*2), velocityUnits::pct); 
    
    
//     //right side
//     RFWheel.spin(directionType::fwd, ((yAxis.value() - xAxis.value())*2), velocityUnits::pct);
//     RMWheel.spin(directionType::fwd, ((yAxis.value() - xAxis.value())*2), velocityUnits::pct);   
//     RBWheel.spin(directionType::fwd, ((yAxis.value() - xAxis.value())*2), velocityUnits::pct);
// }

// TODO
// void grabber(vex::controller::button inBtn, vex::controller::button outBtn){
//     dualButtonMovement(inBtn, outBtn, Grabber);
// }

// TODO
// void lifter(vex::controller::button upBtn, vex::controller::button downBtn){
//     /*
//     //Make so lifter is disabled if ball is in front of Detector and flywheel is not at max speed
//     Brain.Screen.printAt(1,40,flyIsSpinning() ? "true" : "false");
//     Brain.Screen.printAt(1,60,flyIsMaxed() ? "true" : "false");
//     Brain.Screen.printAt(1,80,ballDetected() ? "true" : "false");

//     if(flyIsSpinning() && flyIsMaxed()){
//         dualButtonMovement(upBtn, downBtn, Lifter);
//     }
//     //else if(!flyIsSpinning() && !flyIsMaxed() && !ballDetected()){//sensor connected
//     else if(!flyIsSpinning()){//when sensor is not connected
//         dualButtonMovement(upBtn, downBtn, Lifter);
//     }
//     else{
//         Lifter.stop();
//     }
//     //else if(Override)//TODO add override button
    
//     Brain.Screen.clearScreen();
//     */
    
//     //no ball detector connected
//     dualButtonMovement(upBtn, downBtn, Lifter);
// }

// TODO
// void lift(vex::controller::axis axis){
//     //Left
//     RArm.spin(directionType::fwd,  axis.value(), velocityUnits::pct);
   
//     //Right
//     LArm.spin(directionType::rev,  axis.value(), velocityUnits::pct);
// }

// void flywheel(vex::controller::button stBtn, vex::controller::button stpBtn){
//     void (*st)() = &start;
//     void (*stp)() = &stop;
//     stBtn.pressed(st);
//     stpBtn.pressed(stp);
// }
void pistones(vex::controller::button openBtn, vex::controller::button closeBtn){
    if( openBtn.pressing() ) {
      dig1.set( true );
    }
    else if(closeBtn.pressing()) {
      dig1.set( false );
    }
}
/**********
Autonomous function
**********/

// TODO
// void moveBaseL(double power, velocityUnits vel){//front and back
//     //left
//     LBWheel.spin(directionType::fwd, power, vel);
//     LFWheel.spin(directionType::fwd, power, vel);
//     LMWheel.spin(directionType::fwd, power, vel);
// }

// TODO
// void moveBaseR(double power, velocityUnits vel){//front and back
//     //right
//     RBWheel.spin(directionType::fwd, power, vel);
//     RFWheel.spin(directionType::fwd, power, vel);
//     RMWheel.spin(directionType::fwd, power, vel);
// }

void moveBase(double power, velocityUnits vel){//front and back
    //left
    moveBaseL(power, vel);
    
    //right
    moveBaseR(power, vel);
}

void rotateBase(double power, velocityUnits vel){//positive is clockwise
    //left
    moveBaseL(power, vel);
    
    //right
    moveBaseR(-power, vel);
}

// TODO
// void grab(bool intake){
//     if(intake){
//         Grabber29.spin(directionType::rev, 100, velocityUnits::pct);
//         Grabber.startRotateFor(10, rotationUnits::rev, 100, velocityUnits::pct);
//         Lifter.rotateFor(10, rotationUnits::rev, 100, velocityUnits::pct);
//            }
//     else{
//         Grabber29.spin(directionType::fwd, 100, velocityUnits::pct);
//         Grabber.startRotateFor(-10, rotationUnits::rev, 100, velocityUnits::pct);
//         Lifter.rotateFor(-10, rotationUnits::rev, 100, velocityUnits::pct);
//     }
//     Grabber29.stop();
//     Grabber.stop(brakeType::brake);
// }

// TODO
// void rotateAlt(float revs, double speed){//+ is to cw, - to ccw
//     if(revs < 0){
//         speed = -speed;
//     }
//     //left
//     //moveBaseL(speed, velocityUnits::pct);
//     LMWheel.spin(directionType::fwd, speed, velocityUnits::pct);
//     LFWheel.spin(directionType::fwd, speed, velocityUnits::pct);
//     LBWheel.startRotateFor(revs, rotationUnits::rev, abs(speed), velocityUnits::pct);
    
//     Brain.Screen.printAt(1,40,"Encoder val: %f", RBWheel.rotation(rotationUnits::rev));
//     Brain.Screen.clearScreen();
    
//     //right
//     //cant use function becuase we need to use encoders
//     RMWheel.spin(directionType::fwd, -speed, velocityUnits::pct);
//     RFWheel.spin(directionType::fwd, -speed, velocityUnits::pct);
//     RBWheel.rotateFor(-revs, rotationUnits::rev, abs(speed), velocityUnits::pct);
    
//     baseStop(brakeType::brake);
// }

// void baseStop(brakeType brake){
//     //Left side
//     LBWheel.stop(brake);
//     LFWheel.stop(brake);
//     LMWheel.stop(brake);
    
//     //Right side
//     RBWheel.stop(brake);
//     RFWheel.stop(brake);   
//     RMWheel.stop(brake);
// }

// TODO
// //This function is designed to make a robot move forward.
// void move(float Distance, double speed){
    
//     directionType dir = directionType::fwd;
//     if(Distance < 0)
//         dir = directionType::rev;
    
//     //left
//     LMWheel.spin(dir, speed, velocityUnits::pct);
//     LFWheel.spin(dir, speed, velocityUnits::pct);
//     LBWheel.startRotateFor(Distance, rotationUnits::rev, speed, velocityUnits::pct);
    
//     //right
//     RMWheel.spin(dir, speed, velocityUnits::pct);
//     RFWheel.spin(dir, speed, velocityUnits::pct);
//     RBWheel.rotateFor(Distance, rotationUnits::rev, speed, velocityUnits::pct);
    
    
//     //motorRotateFor(LBWheel, RBWheel, Distance, rotationUnits::rev, speed, velocityUnits::pct);
    
//     baseStop(brakeType::brake);
// }

void moveBack(float Distance, double speed){
    move(-Distance, speed);
}

// TODO
// void intake(float revs, bool intake){
//     if(intake)
//         Grabber.startRotateFor(-revs, rotationUnits::rev, 100, velocityUnits::pct);
//     else
//         Grabber.startRotateFor(revs, rotationUnits::rev, 100, velocityUnits::pct);
// }

// TODO
// void launch(float revs, int flySpeed){
//     startSS(flySpeed);
    
//     if(flySpeed > 5){
//     while(!flyIsMaxed()){
//         task::sleep(10);
//     }
//     }
    
//     if(revs > 0.0){
//     intake(revs);
//     Lifter.rotateFor(revs, rotationUnits::rev, 100, velocityUnits::pct);
//     }
    
//     stop();
// }