#define GLFW_INCLUDE_NONE
#include "event_handler.h"
#include "fractals.h"
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

  EventHandler handler{state, fractal_display.window()};

  const std::string shader_path{PROJECT_DIR};
  Shader shader{(shader_path + "/src/shaders/shader.vert").c_str(),
                (shader_path + "/src/shaders/mandelbrot.frag").c_str()};

  fractal_display.setUniforms(shader);

  while (!glfwWindowShouldClose(fractal_display.window())) {
    fractal_display.clearScreen();
    fractal_display.setUniforms(shader);
    fractal_display.drawFractals();
    handler.checkEvents();
  }

  glfwTerminate();
  return 0;
}
