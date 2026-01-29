// clang-format off
#include "canvas.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "shader_s.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "configuration.h"

#include <glm/fwd.hpp>
#include <iostream>
#include <glm/vec2.hpp>
// clang-format on

// function declaration
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// settings
const glm::vec2 JULIA_CONSTANT{-0.4f, 0.6f};
const glm::vec2 CENTER{-0.1011f, 0.9563f};
const std::string MODE{"mandelbrot"};

// timing
float deltaTime{0.0f};
float lastFrame{0.0f};

// zoom
float zoom{1.0f};
float ZOOM_SPEED{1.0f};

int main() {
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
  GLFWwindow *window{glfwCreateWindow(conf::kScrWidth, conf::kScrHeight,
                                      "FractalsGL", NULL, NULL)};
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // Set correct viewport size
  int fbWidth{}, fbHeight{};
  glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
  glViewport(0, 0, fbWidth, fbHeight);

  glEnable(GL_DEPTH_TEST);

  // build and compile shaders
  const std::string shader_path{PROJECT_DIR};
  Shader shader{(shader_path + "/src/shaders/shader.vert").c_str(),
                (shader_path + "/src/shaders/" + MODE + ".frag").c_str()};

  Canvas canvas{};
  canvas.setupBuffers();

  // activate shaders & set uniforms
  shader.use();
  constexpr float aspect_ratio{static_cast<float>(conf::kScrWidth) /
                               static_cast<float>(conf::kScrHeight)};
  shader.setInt("max_iter", conf::kMaxIteration);
  shader.setFloat("zoom", zoom);
  shader.setVec2("center", CENTER);
  if (MODE == "julia") {
    shader.setVec2("julia_constant", JULIA_CONSTANT);
  }

  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    float currentFrame{static_cast<float>(glfwGetTime())};
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // clear screen & set background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 model{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 projection{glm::ortho(0.0f, conf::kGameWidthf, conf::kGameHeightf,
                                    0.0f, -1.0f, 1.0f)};
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    // activate shaders & update uniforms
    // zoom *= std::exp(deltaTime * ZOOM_SPEED);
    // ourShader.setFloat("zoom", zoom);

    // draw elements
    canvas.draw();

    // swap buffers & poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // terminate glfw
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
