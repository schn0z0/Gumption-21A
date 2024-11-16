#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intake({15, -10});
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
inline ez::Piston mogoMech('G');

