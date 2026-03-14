#define GLFW_INCLUDE_NONE
#include "event_handler.h"
#include "fractals.h"
#include "reference_orbit.h"
#include "shader_s.h"
#include "state.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

int main() {
  AppState state{};

  FractalDisplay fractal_display{state};
  fractal_display.init();

  ReferenceOrbit reference_orbit{};
  reference_orbit.update_reference(state.zoom_center);

  EventHandler handler{state, fractal_display.window()};

  const std::string shader_path{PROJECT_DIR};
  Shader shader{(shader_path + "/src/shaders/shader.vert").c_str(),
                (shader_path + "/src/shaders/mandelbrot.frag").c_str()};

  fractal_display.setUniforms(shader);

  while (!glfwWindowShouldClose(fractal_display.window())) {
    if (state.center_changed) {
      reference_orbit.update_reference(state.zoom_center);
      state.center_changed = false;
    }
    reference_orbit.bind();
    fractal_display.clearScreen();
    fractal_display.setUniforms(shader);
    fractal_display.drawFractals();
    handler.checkEvents();
  }

  glfwTerminate();
  return 0;
}
