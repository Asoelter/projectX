# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/adam/workspace/handmade

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adam/workspace/handmade

# Include any dependencies generated for this target.
include src/CMakeFiles/handmade.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/handmade.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/handmade.dir/flags.make

src/CMakeFiles/handmade.dir/main.cpp.o: src/CMakeFiles/handmade.dir/flags.make
src/CMakeFiles/handmade.dir/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/adam/workspace/handmade/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/handmade.dir/main.cpp.o"
	cd /home/adam/workspace/handmade/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/handmade.dir/main.cpp.o -c /home/adam/workspace/handmade/src/main.cpp

src/CMakeFiles/handmade.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/handmade.dir/main.cpp.i"
	cd /home/adam/workspace/handmade/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/adam/workspace/handmade/src/main.cpp > CMakeFiles/handmade.dir/main.cpp.i

src/CMakeFiles/handmade.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/handmade.dir/main.cpp.s"
	cd /home/adam/workspace/handmade/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/adam/workspace/handmade/src/main.cpp -o CMakeFiles/handmade.dir/main.cpp.s

# Object files for target handmade
handmade_OBJECTS = \
"CMakeFiles/handmade.dir/main.cpp.o"

# External object files for target handmade
handmade_EXTERNAL_OBJECTS =

handmade: src/CMakeFiles/handmade.dir/main.cpp.o
handmade: src/CMakeFiles/handmade.dir/build.make
handmade: /usr/lib/x86_64-linux-gnu/libasound.so
handmade: /usr/lib/x86_64-linux-gnu/libopenal.so
handmade: /usr/lib/x86_64-linux-gnu/libSM.so
handmade: /usr/lib/x86_64-linux-gnu/libICE.so
handmade: /usr/lib/x86_64-linux-gnu/libX11.so
handmade: /usr/lib/x86_64-linux-gnu/libXext.so
handmade: src/CMakeFiles/handmade.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/adam/workspace/handmade/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../handmade"
	cd /home/adam/workspace/handmade/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/handmade.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/handmade.dir/build: handmade

.PHONY : src/CMakeFiles/handmade.dir/build

src/CMakeFiles/handmade.dir/clean:
	cd /home/adam/workspace/handmade/src && $(CMAKE_COMMAND) -P CMakeFiles/handmade.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/handmade.dir/clean

src/CMakeFiles/handmade.dir/depend:
	cd /home/adam/workspace/handmade && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adam/workspace/handmade /home/adam/workspace/handmade/src /home/adam/workspace/handmade /home/adam/workspace/handmade/src /home/adam/workspace/handmade/src/CMakeFiles/handmade.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/handmade.dir/depend

