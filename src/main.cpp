// clang-format off
#include "canvas.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "shader_s.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "configuration.h"
#include "fractals.h"

#include <glm/fwd.hpp>
#include <iostream>
#include <glm/vec2.hpp>
// clang-format on

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

AppState state{};

// settings
const glm::vec2 JULIA_CONSTANT{-0.4f, 0.6f};
const std::string MODE{"mandelbrot"};

// timing
float deltaTime{0.0f};
float lastFrame{0.0f};

// zoom
float zoom{1.0f};

void setupShaders(const std::string_view vert, const std::string_view frag) {
  Shader shader{vert.data(), frag.data()};

  shader.use();
  shader.setInt("max_iter", conf::kMaxIteration);
}

int main() {
  FractalDisplay fractal_display{state};
  fractal_display.init();

  glfwSetFramebufferSizeCallback(fractal_display.window(),
                                 framebuffer_size_callback);
  glfwSetScrollCallback(fractal_display.window(), scroll_callback);
  glfwSetCursorPosCallback(fractal_display.window(), mouse_callback);

  const std::string shader_path{PROJECT_DIR};
  Shader shader{(shader_path + "/src/shaders/shader.vert").c_str(),
                (shader_path + "/src/shaders/" + MODE + ".frag").c_str()};

  fractal_display.setUniforms(shader);
  while (!glfwWindowShouldClose(fractal_display.window())) {
    fractal_display.clearScreen();
    fractal_display.setUniforms(shader);
    fractal_display.drawFractals();
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  zoom += (float)yoffset * conf::kScrollSpeed;
  std::cout << zoom << '\n';
  if (zoom <= 0.1f)
    zoom = 0.1f;
  if (zoom > 10.0f)
    zoom = 10.0f;
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  // TODO: Fix zooming in
  const float x{
      (2.0f * static_cast<float>(xpos) / static_cast<float>(conf::kScrWidth)) -
      1.0f};
  const float y{-(
      (2.0f * static_cast<float>(ypos) / static_cast<float>(conf::kScrHeight)) -
      1.0f)};
  state.zoom_center = {x, y};
}
