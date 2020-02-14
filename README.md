The design objective of our Vex V5 custom framework is to work as a set of pre-built functions that can be used for later seasons within the V5 eco-system. It is supposed to allow multiple robots to use the same basic functions without need for any changes within the existing methods and classes.

Features:
- Integrated sensor-using functions for autonomous use
- Custom implementation of PID for usage in precision-heavy movements
- Simple to initialize new robots
- Same source code can be used for multiple robots. Only changes recquired is the robot instance that is used on the main file.

Usage:
- Each project starts with a new custom class that inherits from the base Robot class. This is similar to how other frameworks function (such as React.js for website development)
- In this custom class the program will assign the specific motor configurations for the robot.
- They will also need to implement the basic functions:driver, auton, move_base, grab, and rotate_base. Since they are necessary for the V5 ecosystem to function properly in a competition context. 
- Some of these functions (move_base, rotate_base, and grab) are required for the programmers simplicity, since they are the most commonly used functions in the autonomous method. However, it is not required to implement these functions if you wish to make the complete call to the Auton instance method; you can just opt to leave the method blank
- When developing the driver and auton functions you can leverage the movement package that will provide all the methods necessary for any possible movement for the robot
- The Position class allows for easy automatic direction detection when in the beginning of a match.