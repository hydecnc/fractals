#include "event_handler.h"
#include "GLFW/glfw3.h"
#include "configuration.h"

EventHandler::EventHandler(AppState &appstate, GLFWwindow *window)
    : m_appstate{appstate} {
  glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));

  glfwSetFramebufferSizeCallback(window,
                                 EventCallback::framebuffer_size_callback);
  glfwSetScrollCallback(window, EventCallback::scroll_callback);
  glfwSetCursorPosCallback(window, EventCallback::mouse_callback);
}

void EventHandler::handleEvents() const { glfwPollEvents(); }

void EventHandler::zoomInOut(const double yoffset) {
  m_appstate.zoom_scale += (float)yoffset * conf::kScrollSpeed;
  if (m_appstate.zoom_scale <= 0.1f)
    m_appstate.zoom_scale = 0.1f;
  if (m_appstate.zoom_scale > 10.0f)
    m_appstate.zoom_scale = 10.0f;
}

void EventCallback::framebuffer_size_callback(GLFWwindow *window, int width,
                                              int height) {
  EventHandler *handler{
      reinterpret_cast<EventHandler *>(glfwGetWindowUserPointer(window))};
  glViewport(0, 0, width, height);
}

void EventCallback::scroll_callback(GLFWwindow *window, double xoffset,
                                    double yoffset) {
  EventHandler *handler{
      reinterpret_cast<EventHandler *>(glfwGetWindowUserPointer(window))};
  handler->zoomInOut(yoffset);
}

void EventCallback::mouse_callback(GLFWwindow *window, double xpos,
                                   double ypos) {

  EventHandler *handler{
      reinterpret_cast<EventHandler *>(glfwGetWindowUserPointer(window))};
  // TODO: Implement proper zoom center updates
}
