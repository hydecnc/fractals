#ifndef STATE_H_
#define STATE_H_

#include "configuration.h"
#include <glm/vec2.hpp>

struct AppState {
  glm::vec2 zoom_center{conf::kFractalCenter};
  float zoom_scale{1.0f};
};

#endif
