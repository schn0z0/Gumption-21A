#include "main.h"  // IWYU pragma: keep
#include "pros/rtos.hpp"
#include "subsystems.hpp"

int intakeColor = 2;
int spurfly;
typedef struct alliancecolor {
  int alliance;
} alliancecolor;

int target = 0;
bool jammed = false;

void colorDetect() {
  while (true) {
    ringsens.set_led_pwm(50);
    if ((ringsens.get_hue() < 25) && (ringsens.get_hue() > 0)) {
      intakeColor = 1;  // red
      lv_obj_set_style_bg_color(ringind, lv_color_hex(0xff2a00), LV_PART_MAIN);
      lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0xff2a00), LV_PART_MAIN);
    } else if ((ringsens.get_hue() < 225) && (ringsens.get_hue() > 200)) {
      intakeColor = 0;  // blue
      lv_obj_set_style_bg_color(ringind, lv_color_hex(0x0066cc), LV_PART_MAIN);
      lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x0066cc), LV_PART_MAIN);
    } else if ((ringsens.get_hue() < 90) && (ringsens.get_hue() > 70)) {
      spurfly = (spurfly + 1) % 360;  // easter egg
      lv_obj_set_style_bg_color(ringind, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
      lv_obj_set_style_bg_color(mainlabel, lv_color_hsv_to_rgb(spurfly, 100, 100), LV_PART_MAIN);
    } else {
      intakeColor = 2;  // neutral
      lv_obj_set_style_bg_color(ringind, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
      lv_obj_set_style_bg_color(mainlabel, lv_color_hex(0x5d5d5d), LV_PART_MAIN);
    }
    pros::delay(10);
  }
}

void intakeMove(int Target) {
  intake.move(Target);
  target = Target;
}

bool discarding = false;

void discard() {
  discarding = true;
  lbPID.target_set(185);
  pros::delay(450);
  lbPID.target_set(10);
  discarding = false;
}

void unjamTask() {
  int jamtime = 0;
  while (true) {
    if (!jammed && target != 0 && abs(hook.get_actual_velocity()) <= 20) {
      jamtime++;
      if (jamtime > 20) {
        jamtime = 0;
        jammed = true;
      }
    }
    if (jammed) {
      hook.move(-target);
      jamtime++;
      if (jamtime > 20) {
        jamtime = 0;
        jammed = false;
        intakeMove(target);
      }
    }
    pros::delay(10);
  }
}

void ringsensTask() {
  while (true) {
    if (is_color_sorting) {
      // int allianceColor = ((alliancecolor*)assign)->alliance;
      //  cout << ((alliancecolor*)assign)->alliance << endl;
      if ((int)is_red == intakeColor) discard();
    }
    pros::delay(10);
  }
}
