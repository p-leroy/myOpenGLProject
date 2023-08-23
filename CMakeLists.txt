cmake_minimum_required(VERSION 3.23)

project(myOpenGLProject)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
message("SDL2_INCLUDE_DIRS" ${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

add_executable(myOpenGLProject main.cpp)

target_link_libraries(myOpenGLProject ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
