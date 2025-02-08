#ifdef __EMSCRIPTEN__
#include <SDL.h>
#include <SDL_opengles2.h>
#include <emscripten.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengles2.h>
#endif
#include "./shader_s.h"

// Vertex shader
const GLchar *vertexSource = "attribute vec4 position;                      \n"
                             "varying vec3 color;                           \n"
                             "void main()                                   \n"
                             "{                                             \n"
                             "    gl_Position = vec4(position.xyz, 1.0);    \n"
                             "    color = gl_Position.xyz + vec3(0.5);      \n"
                             "}                                             \n";

// Fragment/pixel shader
const GLchar *fragmentSource =
    "precision mediump float;                     \n"
    "varying vec3 color;                          \n"
    "void main()                                  \n"
    "{                                            \n"
    "    gl_FragColor = vec4 ( color, 1.0 );      \n"
    "}                                            \n";

GLuint initShader() {
  // Create and compile vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);

  // Create and compile fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);

  // Link vertex and fragment shader into shader program and use it
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  return shaderProgram;
}

void initGeometry(Shader &shader) {
  // Create vertex buffer object and copy vertex data into it
  GLuint VBO;

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  GLfloat vertices[] = {0.0f, 0.5f, 0.0f,  -0.5f, -0.5f,
                        0.0f, 0.5f, -0.5f, 0.0f};
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Specify the layout of the shader vertex data (positions only, 3 floats)
  GLint posAttrib = glGetAttribLocation(shader.ID, "aPos");
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                        (void *)0);
  glEnableVertexAttribArray(posAttrib);
}

void mainLoop(void *mainLoopArg) {
  SDL_Window *pWindow = (SDL_Window *)mainLoopArg;

  // Clear screen
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  SDL_GL_SwapWindow(pWindow);
}

int main(int argc, char **argv) {
  int width = 512, height = 512;

  // Create SDL window
  SDL_Window *pWindow = SDL_CreateWindow(
      "Hello Triangle Minimal", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height,
      SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);

  // Create OpenGLES 2 context on SDL window
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetSwapInterval(1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GLContext glc = SDL_GL_CreateContext(pWindow);
  printf("INFO: GL version: %s\n", glGetString(GL_VERSION));

  // Set clear color to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Get actual GL window size in pixels, in case of high dpi scaling
  SDL_GL_GetDrawableSize(pWindow, &width, &height);
  printf("INFO: GL window size = %dx%d\n", width, height);
  glViewport(0, 0, width, height);

  // Initialize shader and geometry
  const std::string shader_path{"/home/voidy/dev/cpp/Fractals/src/shaders/"};
  Shader shader((shader_path + "shader.vert").c_str(),
                (shader_path + "julia.frag").c_str());
  shader.use();
  initGeometry(shader);

  // Start the main loop
  void *mainLoopArg = pWindow;

#ifdef __EMSCRIPTEN__
  int fps = 0; // Use browser's requestAnimationFrame
  emscripten_set_main_loop_arg(mainLoop, mainLoopArg, fps, true);
#else
  while (true)
    mainLoop(mainLoopArg);
#endif

  return 0;
}
