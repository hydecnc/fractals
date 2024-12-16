// clang-format off
#include "shader_s.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/fwd.hpp>
#include <iostream>
// #include <utility>
#include <glm/vec2.hpp>
// clang-format on

// function declaration
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// settings
const unsigned int SCR_WIDTH{800};
const unsigned int SCR_HEIGHT{600};
const unsigned int MAX_ITER{100};
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
  // glfw initialization
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window setup
  GLFWwindow *window{
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FractalsGL", NULL, NULL)};
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

  // configure global opengl state
  // glEnable(GL_DEPTH_TEST);

  // build and compile shaders
  const std::string shader_path{
      "/home/hyde/dev/projects/cpp/fractals_opengl/src/shaders/"};
  Shader ourShader{(shader_path + "shader.vert").c_str(),
                   (shader_path + MODE + ".frag").c_str()};

  const float vertices[]{
      // x, y, z
      1.0f,  1.0f,  0.0f, // top right
      1.0f,  -1.0f, 0.0f, // bottom right
      -1.0f, -1.0f, 0.0f, // bottom left
      -1.0f, 1.0f,  0.0f, // top left
  };

  const unsigned int indices[]{
      0, 1, 3, 1, 2, 3,
  };

  unsigned int VBO, VAO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  // bind VAO
  glBindVertexArray(VAO);

  // copy vertices array to VBO for opengl
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // copy indices array to EBO for opengl
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);
  // set vertex attrib pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // activate shaders & set uniforms
  ourShader.use();
  ourShader.setInt("max_iter", MAX_ITER);
  ourShader.setFloat("zoom", zoom);
  ourShader.setVec2("center", CENTER);
  if (MODE == "julia") {
    ourShader.setVec2("julia_constant", JULIA_CONSTANT);
  }

  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    float currentFrame{static_cast<float>(glfwGetTime())};
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // clear screen & set background color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // activate shaders & update uniforms
    ourShader.use();
    zoom *= std::exp(deltaTime * ZOOM_SPEED);
    ourShader.setFloat("zoom", zoom);

    // draw elements
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // swap buffers & poll events
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  // terminate glfw
  glfwTerminate();
  return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
