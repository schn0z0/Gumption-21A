#pragma once

#include "EZ-Template/api.hpp"  // IWYU pragma: keep
#include "api.h"  // IWYU pragma: keep
#include "ui/manualbuilderui.hpp"

// extern pros::task_t ringsorting;

void colorDetect();
void ringsensTask();
void discard();

inline bool is_red = false;
inline bool is_color_sorting = false;