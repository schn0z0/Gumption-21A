#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intake({5, 10});
inline pros::Motor ladyBrown (9);
inline pros::Rotation LBsens (8);
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
inline ez::Piston mogoMech('A');

