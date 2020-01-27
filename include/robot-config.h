using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor BaseLeft1;
extern motor BaseLeft2;
extern motor BaseLeft3;
extern motor BaseRight1;
extern motor BaseRight2;
extern motor BaseRight3;
extern motor RampL;
extern motor RampR;
extern motor RollerL1;
extern motor RollerL2;
extern motor RollerR1;
extern motor RollerR2;
extern led Piston;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );