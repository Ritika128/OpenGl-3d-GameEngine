cmake_minimum_required(VERSION 3.12)
project(OpenGLExample)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/res/shader)

add_executable(OpenGLExample FileShader.cpp)

target_link_libraries(OpenGLExample glfw)
target_link_libraries(OpenGLExample GL)
target_link_libraries(OpenGLExample glew)

