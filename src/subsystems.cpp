#include "subsystems.hpp"

#include "main.h"  // IWYU pragma: keep

void ladybrownTask() {
while(true) {
		ladybrown.move(lbPID.compute(ladybrown.get_position()));
		pros::delay(10);
	}
}