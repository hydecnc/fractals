#ifndef CANVAS_H_
#define CANVAS_H_

#include <glad/glad.h>

class Canvas {
public:
  void setupBuffers();
  void draw() const;

  ~Canvas();

private:
  static constexpr float m_vertices[]{
      1.0f,  1.0f,  // top right
      1.0f,  -1.0f, // bottom right
      -1.0f, 1.0f,  // top left
      -1.0f, -1.0f, // bottom left
      -1.0f, 1.0f,  // top left
      1.0f,  -1.0f, // bottom right
  };
  GLuint m_VAO{};
  GLuint m_VBO{};
};

#endif
