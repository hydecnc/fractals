#ifndef CANVAS_H_
#define CANVAS_H_

#include "configuration.h"
#include <glad/glad.h>

class Canvas {
public:
  void setupBuffers();
  void draw() const;

  ~Canvas();

private:
  static constexpr float m_vertices[]{
      // First triangle
      conf::kGameWidthf, 0.0f,               // top right
      conf::kGameWidthf, conf::kGameHeightf, // bottom right
      0.0f, 0.0f,                            // top left

      // Second triangle
      0.0f, 0.0f,                            // top left
      conf::kGameWidthf, conf::kGameHeightf, // bottom right
      0.0f, conf::kGameHeightf               // bottom left
  };
  GLuint m_VAO{};
  GLuint m_VBO{};
};

#endif
