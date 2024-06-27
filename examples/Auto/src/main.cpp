/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      6/27/2024, 11:15:31 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

vex::brain       Brain;

motor motor_left = motor(0);
motor motor_right = motor(1);

/**
 * @brief Returns the opposite direction.
 * 
 * This function takes a direction of type `directionType` and returns
 * the opposite direction. If the input direction is `forward`, the function 
 * returns `reverse`. Otherwise, it returns `forward`.
 * 
 * @param dir The input direction of type `directionType`.
 * @return The opposite direction of the input direction.
 */
directionType opposite(directionType dir) {
    if (dir == forward) {
        return reverse;
    } else {
        return forward;
    }
}


/**
 * @brief Drives the robot in the specified direction for a given number of revolutions and speed.
 *
 * This function controls both the left and right motors to spin for the specified number of revolutions
 * at the given speed. The function does not wait for the completion of the motor spin commands, allowing
 * both motors to spin simultaneously. It then manually waits for both motors to finish spinning to the 
 * desired position.
 *
 * @param dir The direction in which the motors should spin (forward or reverse).
 * @param revs The number of revolutions the motors should spin.
 * @param speed The speed at which the motors should spin, in revolutions per minute (RPM).
 */
void drive(directionType dir, float revs, float speed) {
    // We have to pass in the units rev and rpm.
        // Additionally, we must pass false in for bool waitForCompletion.
        // This allows us to spin both motors without waiting for the first one to finish.
    motor_left.spinFor(dir, revs, rev, speed, rpm, false);
    motor_right.spinFor(dir, revs, rev, speed, rpm, false);

    // Because we had waitForCompletion as false, we now have to manually wait for the
        // motors to be done spinning to the desired position.
    while (motor_left.isSpinning() || motor_right.isSpinning()) {
        this_thread::sleep_for(5);
    }
}

/**
 * @brief Turns the robot by spinning the motors in opposite directions for a given number of revolutions and speed.
 *
 * This function controls the left motor to spin in the opposite direction of the specified direction,
 * and the right motor to spin in the specified direction. This causes the robot to turn. The function does not wait
 * for the completion of the motor spin commands, allowing both motors to spin simultaneously. It then manually waits
 * for both motors to finish spinning to the desired position.
 *
 * @param dir The direction in which the right motor should spin (forward or reverse). The left motor will spin in the opposite direction.
 * @param revs The number of revolutions the motors should spin.
 * @param speed The speed at which the motors should spin, in revolutions per minute (RPM).
 */
void turn(directionType dir, float revs, float speed) {
    motor_left.spinFor(opposite(dir), revs, rev, speed, rpm, false);
    motor_right.spinFor(dir, revs, rev, speed, rpm, false);

    while (motor_left.isSpinning() || motor_right.isSpinning()) {
        this_thread::sleep_for(5);
    }
}

int main() {

    // this is just an example, I'm sure these numbers are wrong.

    drive(forward, 4, 50);  // Drive forward for 4 revolutions at 50 RPM
    turn(forward, 0.7, 30); // Turn left for 0.7 revolutions at 30 RPM
    drive(forward, 1, 50);  // Drive forward for 1 revolution at 50 RPM
    turn(forward, 0.7, 30); // Turn left for 0.7 revolutions at 30 RPM
    drive(forward, 4, 50);  // Drive forward for 4 revolutions at 50 RPM
    turn(reverse, 0.7, 30); // Turn right for 0.7 revolutions at 30 RPM
    drive(forward, 1, 50);  // Drive forward for 1 revolution at 50 RPM
    turn(reverse, 0.7, 30); // Turn right for 0.7 revolutions at 30 RPM
    drive(forward, 6, 200); // Drive forward for 6 revolutions at 200 RPM
}
