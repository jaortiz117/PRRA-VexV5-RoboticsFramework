#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
// motor BaseLeft1 = motor(PORT5, ratio18_1, false);
// motor BaseLeft2 = motor(PORT12, ratio18_1, false);
// motor BaseLeft3 = motor(PORT15, ratio18_1, false);
// motor BaseRight1 = motor(PORT4, ratio18_1, false);
// motor BaseRight2 = motor(PORT9, ratio18_1, false);
// motor BaseRight3 = motor(PORT10, ratio18_1, false);
motor RampL = motor(PORT14, ratio18_1, false);
motor RampR = motor(PORT20, ratio18_1, false);
// motor RollerL1 = motor(PORT1, ratio18_1, false);
// motor RollerL2 = motor(PORT2, ratio18_1, false);
// motor RollerR1 = motor(PORT18, ratio18_1, false);
// motor RollerR2 = motor(PORT19, ratio18_1, false);
// led Piston = led(Brain.ThreeWirePort.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}