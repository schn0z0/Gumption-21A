#include "main.h"
#include "subsystems.hpp"

bool LBprimed = false;
int LBpos = 0;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-9,10,-8},     // Left Chassis Ports (negative port will reverse it!
    {-1,2,3},  // Right Chassis Ports (negative port will reverse it!)

    4,      // IMU Port
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    360);   // Wheel RPMz

// list of motors to get temperature
pros::Motor intake1(20);
pros::Motor intake2(19);
pros::Motor driveleft1(-9);
pros::Motor driveleft2(10);
pros::Motor driveleft3(-8);
pros::Motor driveright1(-1);
pros::Motor driveright2(2);
pros::Motor driveright3(3);

vector<jas::motors::motordata> motorbar{{intake1, "intake 1"}, {driveleft1, "drive l1"},  {driveleft2, "drive l2"},	 {driveleft3, "drive l3"},
										{intake2, "intake 2"}, {driveright1, "drive r1"}, {driveright2, "drive r2"}, {driveright3, "drive r3"}, {ladyBrown, "lady brown"}};

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  pros::delay(500);  // Stop the user from doing anything while legacy ports configure
  pros::screen::set_pen(0x15171a);
  pros::screen::fill_rect(0, 0, 480, 240);

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using lvgl
  j_auton_selector.jautonpopulate(
		{jas::jasauton(leftside, 2, 2, "Left side auton", "Auton built for the left side of the field, no matter the alliance", 2, 0, false),
		 jas::jasauton(rightside, 2, 2, "Right side auton", "Auton built for the right side of the field, no matter the alliance", 0, 2, false)
		 });


  // Initialize chassis and auton selector
  chassis.initialize();
	_init_fs();
	screeninit();
	master.rumble(".");
	pros::Task tempcheckcontroller(tempcheckctrl);
	pros::Task colordetection(colorDetect);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);	// Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  
  if(lv_tileview_get_tile_act(mainscreen) == autobuilder)
		autocallback();
  else if(lv_tileview_get_tile_act(mainscreen) == manbuilder)
		mancallback();
  else {
		if(noselection == false) {
			printf("Running auton");
			jautonrun();
		}
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = pros::E_MOTOR_BRAKE_BRAKE;
  scrpage = 2;
	lv_event_send(pageswitch, LV_EVENT_CLICKED, NULL);
  ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  
  chassis.drive_brake_set(driver_preference_brake);
  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital_new_press(DIGITAL_X))
        chassis.pid_tuner_toggle();


      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    chassis.opcontrol_tank();  // Tank control
    // chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    if(lv_tileview_get_tile_act(mainscreen) == motortemps) {
			for(int m = 0; m < motorbar.size(); m++) {
				lv_event_send(motorboxes[m], LV_EVENT_REFRESH, NULL);
			}
		}

/*if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
  LBprimed == false ? LBprimed = true : LBprimed = false;
  pros::delay(1000);
}
if(ladyBrownPos.get_angle() < 300 && LBprimed == true) {
  ladyBrown.move(127);
  pros::delay(10);
}
else if (ladyBrownPos.get_angle() > 10 && LBprimed == false) {
  ladyBrown.move(-127);
  pros::delay(10);
}
else ladyBrown.move(0);*/
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
    if (LBsens.get_angle()>30000){                                 // down
      ladyBrown.move_absolute(-280, 200);      // primed
    } else {
      ladyBrown.move_absolute(-25, 200);       // down
    }
  }
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
    if ((LBsens.get_angle()<2000) or (LBsens.get_angle()>30000)){  // primed or down
      ladyBrown.move_absolute(-1400, 200);    // score
    } else {  
      ladyBrown.move_absolute(-25, 200);      // down
    }
  }




  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    intake.move(-127);
  } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
    intake.move(127);
  } else {
    intake.move(0);
}
  mogoMech.button_toggle(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
 
  



}