#include "autons.hpp"
#include "main.h"
#include "subsystems_auton.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 60;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}


///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  
}

///
// Interference example
/*
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
} 

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}
*/
// . . .
// Make your own autonomous functions here!
// . . .
void rightAWP(){
  is_red = true; //is_red means it will sort OUT red, not that you are on red team
  is_color_sorting = true;
intake.move(-80); //intake moves backwards to push rings out of the way better
chassis.pid_drive_set(8_in, 35, true); //
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(-90_deg, TURN_SPEED); //turn towards alliance stake
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(6_in, 35, true); //drive to alliance stake
intake.move(0); 
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-5_in, 45, true); //drive away from alliance stake
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(-50_deg, TURN_SPEED); //turn to mogo
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-34_in, 80, true); //drive to mogo
chassis.pid_wait_until(-29); //this line makes the bot clamp once it gets to the mogo, and then keep going to the desired target
mogoMech.set(true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(180_deg, TURN_SPEED); //turn to safe ring stack
chassis.pid_wait_quick_chain();
intake.move(100); //run intake to pick up rings for the rest of auton
chassis.pid_drive_set(22_in, 80, true); //drive to safe ring stack
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(240_deg, TURN_SPEED); //turn to corner
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(45_in, 60, true); //the rest of the code just makes it ram into the corner 3 times to hopefully pick up all the rings
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-12_in, 60, true);
//hook.move(-25);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 60, true);
//hook.move(120);
}

void leftAWP(){
//Make what I did on the right side work on the left side here :3
}


void newauton(){
}

void newauton2(){
}
  void rightside(){
mogoMech.set(false);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-24_in, 50, true);
chassis.pid_wait_quick_chain();
mogoMech.set(true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(-90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
intake.move(127);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(14_in, 70, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(30_in, 70, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(121_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(16_in, 70, true);
chassis.pid_wait_quick_chain();
intake.move(0);
}
//chassis.pid_wait_quick_chain();
//chassis.pid_turn_set(121_deg, TURN_SPEED);
//chassis.pid_wait_quick_chain();
//chassis.pid_drive_set(16_in, 70, true);
//chassis.pid_wait_quick_chain();

  void leftside(){
mogoMech.set(false);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-24_in, 90, true);
chassis.pid_wait_quick_chain();
mogoMech.set(true);//clamp mogo
chassis.pid_wait_quick_chain();   
chassis.pid_turn_set(90_deg, TURN_SPEED);//turn to ring
chassis.pid_wait_quick_chain();
intake.move(127);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(31.5_in, 140, true); //drive to ring
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(180_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(15_in, 30, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(270_deg, TURN_SPEED, ez::cw);
chassis.pid_drive_set(24_in, 30, true);
chassis.pid_wait_quick_chain();
intake.move(0);}

void skills(){
mogoMech.set(false);
intake.move(127);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-5_in, 90, true);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (10_in, 90, true);
chassis.pid_wait_quick_chain();
intake.move(0);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(-90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-20_in, 40, true); 
chassis.pid_wait_quick_chain();
mogoMech.set(true); //grab 1st MOGO
chassis.pid_turn_set(0_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
intake.move(127);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (22_in, 40, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (20_in, 40, true); // grab first set of rings
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(180_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (42_in, 40, true);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-12_in, 40, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (13_in, 40, true); //grabs 2nd ring
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-4_in, 40, true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(-30_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-28_in, 40, true);
chassis.pid_wait_quick_chain();
mogoMech.set(false);
intake.move(0);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (12_in, 40, true); //put mogo in corner
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set (-72_in, 40, true); //put mogo in corner
chassis.pid_wait_quick_chain();
mogoMech.set(true);
chassis.pid_turn_set(-90_deg, TURN_SPEED); //Hopes and fucking dreams
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(48_in, 40, true);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(-24_in, 40, true);
chassis.pid_turn_set(-90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(48_in, 40, true);
chassis.pid_wait_quick_chain();
mogoMech.set(true);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(27_in, 40, true);
chassis.pid_wait_quick_chain();
intake.move(127);
chassis.pid_wait_quick_chain();
chassis.pid_turn_set(90_deg, TURN_SPEED);
chassis.pid_wait_quick_chain();
chassis.pid_drive_set(60_in, 40, true);
chassis.pid_wait_quick_chain();
intake.move(0);
}

void testautonRed() {
	// ringsorting = pros::c::task_create(ringsensTask, (void *)0, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "ring sorting");
  is_red = true;
  is_color_sorting = true;
  
	mogoMech.set(true);
	intake.move(119);
	chassis.pid_wait();
}