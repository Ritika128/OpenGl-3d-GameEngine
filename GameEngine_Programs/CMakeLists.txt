cmake_minimum_required(VERSION 3.12)
project(OpenGLExample)

find_package(OpenGL REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/glm-master)

add_executable(OpenGLExample Rotation.cpp)

target_link_libraries(OpenGLExample glfw)
target_link_libraries(OpenGLExample OpenGL::GL)
target_link_libraries(OpenGLExample DGL_GLEXT_PROTOTYPES)

