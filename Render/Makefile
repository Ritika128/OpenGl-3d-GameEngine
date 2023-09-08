# This makefile is used to compile openGL programs

OPENGL_FLAGS =  -framework Cocoa -framework OpenGL -framework IOKit
GLFW_flags = -lglfw3
CFLAGS = -std=c++17 -fdiagnostics-color=always -Wall -Wdeprecated-declarations #-Wno-deprecated

## Compile and link any .cpp program mentioned in "make *.cpp"

all: $(patsubst %.cpp, %, $(wildcard *.cpp))

%: %.cpp 
	clang++ $(GLFW_flags) $(OPENGL_FLAGS) $(CFLAGS) $^ -o $@ -v

#for all *cpp files, clean their corresponding executables
clean:
	rm -f $(patsubst %.cpp, %, $(wildcard *.cpp))
