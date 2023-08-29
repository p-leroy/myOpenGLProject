cmake_minimum_required(VERSION 3.23)

project(myOpenGLProject)

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
