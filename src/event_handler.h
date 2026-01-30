#include "state.h"
#include <GLFW/glfw3.h>

class EventHandler {
public:
  EventHandler(AppState &appstate, GLFWwindow *window);

  void handleEvents() const;
  void zoomInOut(const double yoffset);
  void panScreen(const double deltaX, const double deltaY);
  void handleMouseButton(GLFWwindow *window, const int button, const int action,
                         const int mods);
  void handleMouseMove(const double xpos, const double ypos);

private:
  AppState &m_appstate;
  bool m_isDragging{false};
  double m_lastMouseX{}, m_lastMouseY{};
  double m_dragStartX{}, m_dragStartY{};
};

namespace EventCallback {
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods);
}; // namespace EventCallback
