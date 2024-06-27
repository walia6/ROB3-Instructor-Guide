/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/27/2024, 12:39:37 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

vex::brain Brain;

motor motor_arm = motor(4);

controller controller1 = controller();

float max_voltage = 12;
float arm_power = 0.5;

int main() {
    while (true) {
        
        if (controller1.ButtonUp.pressing()) {
            motor_arm.spin(forward, max_voltage * arm_power, volt);
        } else if (controller1.ButtonDown.pressing()) {
            motor_arm.spin(reverse, max_voltage * arm_power, volt);
        } else {
            motor_arm.stop(hold);
        }

        this_thread::sleep_for(5);
    }
}
