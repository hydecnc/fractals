cmake_minimum_required(VERSION 3.30)
project(Fractals VERSION 1.0)

# Generate complie commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Specifying the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create an option to switch between a system sdl Library and a vendored SDL Library
# option(FRACTALS_VENDORED "Use vendored libraries" OFF)
#
# if(FRACTALS_VENDORED)
#   add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
# else()
#   find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
# endif()

# Get all header files
set(HEADER_FILES
  # src/shader_s.h
)

# Get all source files
set(SOURCE_FILES
  src/main.c
)

# Create executable
add_executable(${PROJECT_NAME}
  ${SOURCE_FILES}
  ${HEADER_FILES}
)

# Emscripten-specific settings
if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
  # set(CMAKE_EXECUTABLES_SUFFIX ".html")
  # target_link_options(${PROJECT_NAME} PRIVATE --preload-file .)
  set(USE_FLAGS "-s USE_SDL=2 -o main.html")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
  set(CMAKE_EXECUTABLE_SUFFIX .html)
  # target_link_options(${PROJECT_NAME} PRIVATE -sUSE_SDL=2)
else()
  find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})


