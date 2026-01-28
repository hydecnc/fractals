cmake_minimum_required(VERSION 3.20)
project(fractals VERSION 1.0)

# Generate complie commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specifying the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_VENDORED "Use vendored libraries" ON)

if (USE_VENDORED) 
  add_subdirectory(vendored/glfw EXCLUDE_FROM_ALL)
  add_subdirectory(vendored/glm EXCLUDE_FROM_ALL)
else()
  find_package(glfw3 REQUIRED)
  find_package(glm REQUIRED)
endif()


# Find OpenGL Package
find_package(OpenGL REQUIRED)

include_directories(
  include
  ${OpenGL_INCLUDE_DIRS}
  ${glfw3_INCLUDE_DIRS}
)

# Get all header files
set(HEADER_FILES
  src/shader_s.h
)

# Get all source files
set(SOURCE_FILES
  src/main.cpp
  src/glad.c
)

# Add the source files
add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

# Link against OpenGL and GLFW
target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARIES} glfw glm::glm)
