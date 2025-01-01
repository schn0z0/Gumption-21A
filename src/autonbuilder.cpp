#include "main.h"  // IWYU pragma: keep

void testautonbuilder() {
	pros::Task ringsort(ringsensTask, (void*)"0");
	chassis.odom_pose_set({48_in, 21_in, 180_deg});
	left_mogo();
	left_btm_ring();
	red_ring_rush();
	mogoMech.set(false);
	mid_top_ring();
	alliancestake();
	ladder();
}

void goal_rush() {
	//doinker/goal rush mogo mech here
	chassis.pid_odom_set(62_in, 127, false);
	chassis.pid_wait();
	chassis.pid_odom_set(-24_in, 127, false);
	chassis.pid_wait_quick_chain();
	chassis.pid_turn_set(180_deg, 127);
	chassis.pid_wait();
}

void alliancestake() {
	intake.move(0);
	chassis.pid_odom_set({{72_in, 24_in, 180_deg}, fwd, 127});
	chassis.pid_wait_quick_chain();
	intake.move(127);
	chassis.pid_odom_set(-12_in, 127, false);
	if(chassis.interfered) return;
	chassis.pid_wait();
}


void blue_gr_mogo() {
	if(chassis.odom_x_get() >= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	chassis.pid_odom_set({{24_in, 48_in}, rev, 90});
	chassis.pid_wait();
	mogoMech.set(true);
	chassis.pid_wait();
}

void red_gr_mogo() {
	if(chassis.odom_x_get() <= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	chassis.pid_odom_set({{120_in, 48_in}, rev, 90});
	chassis.pid_wait();
	mogoMech.set(true);
	chassis.pid_wait();
}

void left_mogo() {
	if(chassis.odom_x_get() >= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	chassis.pid_odom_set({{48_in, 48_in}, rev, 90});
	chassis.pid_wait();
	mogoMech.set(true);
	chassis.pid_wait();
}

void right_mogo() {
	if(chassis.odom_x_get() <= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	chassis.pid_odom_set({{96_in, 48_in}, rev, 90});
	chassis.pid_wait();
	mogoMech.set(true);
	chassis.pid_wait();
}

void left_corner() {
	if(chassis.odom_x_get() >= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	// corner rush
}

void right_corner() {
	if(chassis.odom_x_get() <= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	// corner rush
}

void red_ring_rush() {
	if(chassis.odom_x_get() >= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	intake.move(127);
	chassis.pid_odom_set({{{14_in, 58_in, 45_deg}, fwd, 127}, {{34_in, 61_in, 90_deg}, fwd, 60}});
	chassis.pid_wait();
}

void blue_ring_rush() {
	if(chassis.odom_x_get() <= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	intake.move(127);
	chassis.pid_odom_set({{{130_in, 58_in, 315_deg}, fwd, 127}, {{110_in, 63_in, 270_deg}, fwd, 60}});
	chassis.pid_wait();
}

void left_btm_ring() {
	if(chassis.odom_x_get() >= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	intake.move(127);
	chassis.pid_odom_set({{24_in, 48_in}, fwd, 127});
	chassis.pid_wait();
}

void mid_top_ring() {
	//piston actuated intake here
	intake.move(127);
	chassis.pid_odom_set( {{72_in, 24_in}, fwd, 127});
	//chassis.pid_wait();
	//piston actuated intake here
	chassis.pid_wait();
}

void right_btm_ring() {
	if(chassis.odom_x_get() <= 72 && chassis.odom_y_get() > 36) {
		chassis.pid_odom_set({{72_in, 24_in}, fwd, 127});
		chassis.pid_wait_quick_chain();
	}
	intake.move(127);
	chassis.pid_odom_set({{120_in, 48_in}, fwd, 127});
	chassis.pid_wait();
}

void ladder() {
	pros::delay(2000);
	//set lady brown up so it touches the ladder
	chassis.pid_odom_set({{72_in, 60_in}, fwd, 127});
	chassis.pid_wait();
}