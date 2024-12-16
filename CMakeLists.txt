cmake_minimum_required(VERSION 3.20)
project(Fractals VERSION 1.0)

# Generate complie commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specifying the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find OpenGL Package
find_package(OpenGL REQUIRED)

# Find GLFW Package
find_package(glfw3 REQUIRED)

# Find glm Package
find_package(glm REQUIRED)

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
include_directories(
  ${OpenGL_INCLUDE_DIRS}
  ${glfw3_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)


# Link against OpenGL and GLFW
# target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARIES} ${glfw3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenGL_LIBRARIES} glfw glm::glm)
