#pragma once

#include "EZ-Template/api.hpp"  // IWYU pragma: keep
#include "api.h"  // IWYU pragma: keep

// extern pros::task_t ringsorting;
extern bool jammed;
extern int target;
void intakeMove(int target);
void colorDetect();
void ringsensTask();
void discard();
void unjamTask();

inline bool is_red = false;
inline bool is_color_sorting = false;