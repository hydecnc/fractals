#include "event_handler.h"
#include "GLFW/glfw3.h"
#include "configuration.h"
#include <algorithm>
#include <cmath>

EventHandler::EventHandler(AppState &appstate, GLFWwindow *window)
    : m_appstate{appstate} {
  glfwSetWindowUserPointer(window, reinterpret_cast<void *>(this));

  glfwSetFramebufferSizeCallback(window,
                                 EventCallback::framebuffer_size_callback);
  glfwSetScrollCallback(window, EventCallback::scroll_callback);
  glfwSetCursorPosCallback(window, EventCallback::cursor_pos_callback);
  glfwSetMouseButtonCallback(window, EventCallback::mouse_button_callback);
}

void EventHandler::handleEvents() const { glfwPollEvents(); }

void EventHandler::zoomInOut(const double yoffset) {
  m_appstate.zoom_scale *= pow(conf::kScrollSpeed, yoffset);
  m_appstate.zoom_scale = std::clamp(m_appstate.zoom_scale, conf::kMinZoomScale,
                                     conf::kMaxZoomScale);
}

void EventHandler::panScreen(const double deltaX, const double deltaY) {
  m_appstate.zoom_center.x -=
      deltaX * conf::kPanSensitivity / m_appstate.zoom_scale;
  m_appstate.zoom_center.y +=
      deltaY * conf::kPanSensitivity / m_appstate.zoom_scale;
}

void EventHandler::handleMouseButton(GLFWwindow *window, const int button,
                                     const int action, const int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    if (action == GLFW_PRESS) {
      glfwGetCursorPos(window, &m_dragStartX, &m_dragStartY);
      m_lastMouseX = m_dragStartX;
      m_lastMouseY = m_dragStartY;
      m_isDragging = true;
    } else if (action == GLFW_RELEASE) {
      m_isDragging = false;
    }
  }
}

void EventHandler::handleMouseMove(const double xpos, const double ypos) {
  if (m_isDragging) {
    const double deltaX = xpos - m_lastMouseX;
    const double deltaY = ypos - m_lastMouseY;

    panScreen(deltaX, deltaY);

    m_lastMouseX = xpos;
    m_lastMouseY = ypos;
  }
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

void EventCallback::cursor_pos_callback(GLFWwindow *window, double xpos,
                                        double ypos) {

  EventHandler *handler{
      reinterpret_cast<EventHandler *>(glfwGetWindowUserPointer(window))};
  handler->handleMouseMove(xpos, ypos);
}

void EventCallback::mouse_button_callback(GLFWwindow *window, int button,
                                          int action, int mods) {
  EventHandler *handler{
      reinterpret_cast<EventHandler *>(glfwGetWindowUserPointer(window))};
  handler->handleMouseButton(window, button, action, mods);
}
