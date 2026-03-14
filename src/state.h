#ifndef STATE_H_
#define STATE_H_

#include "configuration.h"

struct AppState {
  std::complex<float> zoom_center{conf::kFractalCenter};
  float zoom_scale{conf::kInitialZoom};
  bool center_changed{false};
};

#endif
