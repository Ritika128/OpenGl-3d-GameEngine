# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anish/Desktop/OpenGL/Tut_Programs/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anish/Desktop/OpenGL/Tut_Programs/src

# Include any dependencies generated for this target.
include CMakeFiles/OpenGLExample.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGLExample.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGLExample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGLExample.dir/flags.make

CMakeFiles/OpenGLExample.dir/FileShader.cpp.o: CMakeFiles/OpenGLExample.dir/flags.make
CMakeFiles/OpenGLExample.dir/FileShader.cpp.o: FileShader.cpp
CMakeFiles/OpenGLExample.dir/FileShader.cpp.o: CMakeFiles/OpenGLExample.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anish/Desktop/OpenGL/Tut_Programs/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGLExample.dir/FileShader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGLExample.dir/FileShader.cpp.o -MF CMakeFiles/OpenGLExample.dir/FileShader.cpp.o.d -o CMakeFiles/OpenGLExample.dir/FileShader.cpp.o -c /home/anish/Desktop/OpenGL/Tut_Programs/src/FileShader.cpp

CMakeFiles/OpenGLExample.dir/FileShader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenGLExample.dir/FileShader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anish/Desktop/OpenGL/Tut_Programs/src/FileShader.cpp > CMakeFiles/OpenGLExample.dir/FileShader.cpp.i

CMakeFiles/OpenGLExample.dir/FileShader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenGLExample.dir/FileShader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anish/Desktop/OpenGL/Tut_Programs/src/FileShader.cpp -o CMakeFiles/OpenGLExample.dir/FileShader.cpp.s

# Object files for target OpenGLExample
OpenGLExample_OBJECTS = \
"CMakeFiles/OpenGLExample.dir/FileShader.cpp.o"

# External object files for target OpenGLExample
OpenGLExample_EXTERNAL_OBJECTS =

OpenGLExample: CMakeFiles/OpenGLExample.dir/FileShader.cpp.o
OpenGLExample: CMakeFiles/OpenGLExample.dir/build.make
OpenGLExample: CMakeFiles/OpenGLExample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anish/Desktop/OpenGL/Tut_Programs/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenGLExample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenGLExample.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGLExample.dir/build: OpenGLExample
.PHONY : CMakeFiles/OpenGLExample.dir/build

CMakeFiles/OpenGLExample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenGLExample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenGLExample.dir/clean

CMakeFiles/OpenGLExample.dir/depend:
	cd /home/anish/Desktop/OpenGL/Tut_Programs/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anish/Desktop/OpenGL/Tut_Programs/src /home/anish/Desktop/OpenGL/Tut_Programs/src /home/anish/Desktop/OpenGL/Tut_Programs/src /home/anish/Desktop/OpenGL/Tut_Programs/src /home/anish/Desktop/OpenGL/Tut_Programs/src/CMakeFiles/OpenGLExample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenGLExample.dir/depend
