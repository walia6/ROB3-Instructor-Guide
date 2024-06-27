/*
    In here I have the base tank drive and I've also added some button stuff. Two separate buttons to open and close the claw.
    Additionally, I show how to have one button toggle the claw on and off.
*/

#include "vex.h"

using namespace vex;

vex::brain Brain;

motor motor_left = motor(0);

motor motor_right = motor(1, true); 

// instantiate our claw motor;
motor motor_claw = motor(2);

controller controller1 = controller();

float max_voltage = 12;


void openClaw() {
    motor_claw.spin(forward, max_voltage, volt);

    // we want to wait half a second for the claw to fully get to the open or closed state, and then put the brakes on.
        // we have to do this because keeping the motor runnin while it cant push the claw open anymore will overheat the motor.
        // this is not inherently dangerous as the motor will just shut itself off until its cool, but kids wont understand
        // why their stuff isn't working anymore.
    this_thread::sleep_for(500);
    motor_claw.stop(hold);
}

void closeClaw() {
    motor_claw.spin(reverse, max_voltage, volt);
    this_thread::sleep_for(500);
    motor_claw.stop(hold);
}

bool clawToggle = true;

// this is the event to be called when the Up button is pressed
void toggleClaw() {
    if (clawToggle) {
        openClaw();
    } else {
        closeClaw();
    }
    clawToggle = !clawToggle;
}

int main() {

    // Here we register the functions to the buttons. We should do this inside of main, but NOT within the main loop
    controller1.ButtonUp.pressed(openClaw);

    controller1.ButtonDown.pressed(closeClaw);

    controller1.ButtonX.pressed(toggleClaw);

    while(true) {

        int axis3pos = controller1.Axis3.position();
        int axis2pos = controller1.Axis2.position();

        float left_voltage = axis3pos / 100.0 * max_voltage;
        float right_voltage = axis2pos / 100.0 * max_voltage;
        
        motor_left.spin(forward, left_voltage, volt);
        motor_right.spin(forward, right_voltage, volt);

        this_thread::sleep_for(5); 
    }
}
