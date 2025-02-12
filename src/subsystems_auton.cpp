#include "main.h"  // IWYU pragma: keep

int intakeColor = 2;
int spurfly;
typedef struct alliancecolor {
	int alliance;
} alliancecolor;

void colorDetect() {
	while(true) {
		ringsens.set_led_pwm(50);
		if((ringsens.get_hue() < 25) && (ringsens.get_hue() > 0)) {
			intakeColor = 1;  // red
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0xff2a00), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0xff2a00), LV_PART_MAIN);
			lv_obj_set_style_bg_color(builderringind, lv_color_hex(0xff2a00), LV_PART_MAIN);
		} else if((ringsens.get_hue() < 225) && (ringsens.get_hue() > 200)) {
			intakeColor = 0;  // blue
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0x0066cc), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x0066cc), LV_PART_MAIN);
			lv_obj_set_style_bg_color(builderringind, lv_color_hex(0x0066cc), LV_PART_MAIN);
		} else if((ringsens.get_hue() < 90) && (ringsens.get_hue() > 70)) {
			spurfly = (spurfly + 1) % 360;	// easter egg
			lv_obj_set_style_bg_color(ringind, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
			lv_obj_set_style_bg_color(builderringind, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
		} else {
			intakeColor = 2;  // neutral
			lv_obj_set_style_bg_color(ringind, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
			lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
			lv_obj_set_style_bg_color(builderringind, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
		}
		pros::delay(10);
	}
}

bool discarding = false;

void discard() {
discarding = true;
	hook.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	double voltage = hook.get_voltage();
		pros::delay(140);
	hook.move(0);
	pros::delay(300);
	int target = (int)hook.get_position() % 1000;
	hook.move_relative(2000 - target, 200);
	pros::delay(500);
	hook.set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	hook.move(abs(voltage));
	discarding = false;
}

void ringsensTask() {
	while(true) {
		if (is_color_sorting) {
			//int allianceColor = ((alliancecolor*)assign)->alliance;
			// cout << ((alliancecolor*)assign)->alliance << endl;
			if((int)is_red == intakeColor) discard();
		}
		pros::delay(10);
	}
}