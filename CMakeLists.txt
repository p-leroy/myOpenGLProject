cmake_minimum_required(VERSION 3.23)

project(myOpenGLProject)

#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})
#message("SDL2_INCLUDE_DIRS " ${SDL2_INCLUDE_DIRS})
#message("SDL2_LIBRARIES " ${SDL2_LIBRARIES})

#find_package(SDL2_IMAGE REQUIRED)
#include_directories("C:/opt/SDL2_image-devel-2.6.3-VC/SDL2_image-2.6.3/include")

#find_package(OpenGL REQUIRED)
#message("OPENGL_LIBRARIES " ${OPENGL_LIBRARIES})

#find_package(GLEW REQUIRED)
#include_directories("C:/opt/glew-2.2.0-win32/glew-2.2.0/include")
#set(GLEW_LIBRARY "C:/opt/glew-2.2.0-win32/glew-2.2.0/lib/Release/x64/glew32.dll")
#message("GLEW_LIBRARY " ${GLEW_LIBRARY})

# GLFW
include_directories("C:/opt/glfw-3.3.8.bin.WIN64/include")
set(GLFW_LIBRARY "C:/opt/glfw-3.3.8.bin.WIN64/lib-vc2015/glfw3.lib")
message("GLFW_LIBRARY " ${GLFW_LIBRARY})

# GLAD
include_directories("./glad/include")

add_executable(myOpenGLProject)

target_sources(${PROJECT_NAME} PRIVATE
    main.cpp
    stb.cpp
    ./glad/src/glad.c)

target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARY})

