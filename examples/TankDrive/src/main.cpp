/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Archy                                                     */
/*    Created:      6/27/2024, 7:42:19 AM                                     */
/*    Description:  This is a popular and easy-to-implement control scheme    */
/*                      for robotics called Tank Drive. The left joystick     */
/*                      controls the left motor(s), and the right joystick    */
/*                      controls the right motor(s).                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
// define your global instances of motors and other devices 

// motor(0) is how you instantiate a motor in Port 1. Subtract one.
motor motor_left = motor(0);

// The second parameter `bool reverse` should be set for one side of the motors, so that they spin the same direction
motor motor_right = motor(1, true); 

// Instatiating a controller is simple.
controller controller1 = controller();

// The motors are 12 volt.
float max_voltage = 12;

// main is the entry point of the program. Any variables to be declared should be done outside of main. Everything else should be in here.
int main() {

    // We want to continuously and repeatedly set the motors to spin at a voltage based off the joystick positions
    while(true) {

        // There are four axes - two for each joystick. Axis 3 and 2 are the vertical axes for the left and right joystick respectively.
        // controller::axis::position gets the position of the joystick axis on a scale from -100 to 100 as an int. (+100 is up or to the right)
        int axis3pos = controller1.Axis3.position();
        int axis2pos = controller1.Axis2.position();

        // I take a few minutes here to show the math on the board how for I derived the formulas for the voltage.
        float left_voltage = axis3pos / 100.0 * max_voltage;
        float right_voltage = axis2pos / 100.0 * max_voltage;

        // We can simply spin the motors forward at left or right_voltage 
            // because a negative voltage in a forward direction will spin motor in reverse.
        motor_left.spin(forward, left_voltage, volt); // We have to pass in units for potential for electric potential for some reason 
        motor_right.spin(forward, right_voltage, volt);

        // If we dont sleep on occasion the brain will terminate our program
        this_thread::sleep_for(5); // This is in miliseconds
    }
}
