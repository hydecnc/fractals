// clang-format off
#include "canvas.h"
#include "shader_s.h"
#include "state.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

class FractalDisplay {
public:
  FractalDisplay(const AppState &state);
  int init();

  void clearScreen() const;
  void drawFractals() const;
  void setupShaders(const std::string_view vert, const std::string_view frag);
  void setUniforms(const Shader &shader) const;

  GLFWwindow *window() const;

private:
  GLFWwindow *m_window{};
  Canvas m_canvas{};
  const AppState &m_state{};

  float m_zoom{1.0f};

  void setViewport();
};
