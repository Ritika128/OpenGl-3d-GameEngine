OPENGL_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
GLFW_flags = -lglfw3
CXX = g++
CXXFLAGS = -std=c++17 -fdiagnostics-color=always -Wall
OFLAGS = -I/Users/ritikanankar/OpenGLGame/OGL3D/include/OGL3D/Window/Game
WFLAGS = -I/Users/ritikanankar/OpenGLGame/OGL3D/include/OGL3D/Window/Window/OWindow.h

# Directories
SRC_DIR = OpenGLGame/OGL3D/source/Game
GLAD_DIR = OpenGLGame/OGL3D/glad
OGLGAME_DIR = OpenGLGame/Game

# Source files
GLAD_SRC = $(GLAD_DIR)/src/glad.c
OGLGAME_SRC = $(OGLGAME_DIR)/main.cpp $(SRC_DIR)/OGame.cpp
# OGL3D_SRC = $(SRC_DIR)/OGL3D/Window/OWindow.cpp

# Executable names
# EXECUTABLES = main OGame

# all: $(EXECUTABLES)
all : $(patsubst %.cpp, %, $(wildcard *.cpp))

%: %.cpp
	$(OGLGAME_SRC) $(OGL3D_SRC) $(GLAD_SRC) $(OFLAGS) $(WFLAGS)
	$(CXX) $(CXXFLAGS) $(OPENGL_FLAGS) $(GLFW_flags) $^ -o $@ -v

