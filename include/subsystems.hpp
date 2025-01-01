#pragma once

#include "EZ-Template/piston.hpp"
#include "api.h"
#include "pros/motor_group.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
// Your motors, sensors, etc. should go here.  Below are examples
inline pros::MotorGroup intake({20, 19});
inline pros::Motor ladyBrown (5);
inline pros::Rotation LBsens (6);

//only keeping this bit in because some of the code relies on it as a variable, just change it to an unused port or get an optical sensor
inline pros::Optical ringsens(7);
// inline pros::Motor intake(1);
// inline pros::adi::DigitalIn limit_switch('A');
inline ez::Piston mogoMech('A');

