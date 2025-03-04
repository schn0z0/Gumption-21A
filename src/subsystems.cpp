#include "subsystems.hpp"

#include "main.h"  // IWYU pragma: keep
#include "pros/misc.h"

void ladybrownTask() {
while(true) {
		ladybrown.move(lbPID.compute(ladybrown.get_position()));
		pros::delay(10);
	}
}