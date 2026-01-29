#include "fractals.h"
#include "configuration.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

FractalDisplay::FractalDisplay(const AppState &state) : m_state{state} {}

int FractalDisplay::init() {
  if (glfwPlatformSupported(GLFW_PLATFORM_WAYLAND)) {
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
  } else {
    std::cout << "No Wayland Support\n";
  }

  // glfw initialization
  glfwInit();
  glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window setup
  m_window = glfwCreateWindow(conf::kScrWidth, conf::kScrHeight, "FractalsGL",
                              NULL, NULL);
  if (m_window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(m_window);
  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  setViewport();
  glEnable(GL_DEPTH_TEST);
  m_canvas.setupBuffers();

  return 0;
}

void FractalDisplay::setUniforms(const Shader &shader) const {
  shader.use();
  shader.setInt("max_iter", conf::kMaxIteration);

  glm::mat4 model{1.0f};
  glm::mat4 view{1.0f};
  glm::mat4 projection{glm::ortho(0.0f, conf::kGameWidthf, conf::kGameHeightf,
                                  0.0f, -1.0f, 1.0f)};
  shader.setMat4("model", model);
  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  shader.setVec2("center", m_state.zoom_center);
  shader.setFloat("zoom", m_zoom);
}

void FractalDisplay::clearScreen() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void FractalDisplay::drawFractals() const {
  // per-frame time logic
  // float currentFrame{static_cast<float>(glfwGetTime())};
  // float deltaTime = currentFrame - lastFrame;
  // float lastFrame = currentFrame;

  m_canvas.draw();

  glfwSwapBuffers(m_window);
}

GLFWwindow *FractalDisplay::window() const { return m_window; }

void FractalDisplay::setViewport() {
  // Set correct viewport size
  int fbWidth{}, fbHeight{};
  glfwGetFramebufferSize(m_window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);
}
