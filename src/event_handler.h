#include "state.h"
#include <GLFW/glfw3.h>

class EventHandler {
public:
  EventHandler(AppState &appstate, GLFWwindow *window);

  void handleEvents() const;
  void zoomInOut(const double yoffset);

private:
  AppState &m_appstate;
};

namespace EventCallback {
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
}; // namespace EventCallback
