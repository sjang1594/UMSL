# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/139/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/139/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/seungho/project/UMSL/CS6420/project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/seungho/project/UMSL/CS6420/project1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p.dir/flags.make

CMakeFiles/p.dir/operator.cpp.o: CMakeFiles/p.dir/flags.make
CMakeFiles/p.dir/operator.cpp.o: ../operator.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungho/project/UMSL/CS6420/project1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p.dir/operator.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p.dir/operator.cpp.o -c /home/seungho/project/UMSL/CS6420/project1/operator.cpp

CMakeFiles/p.dir/operator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p.dir/operator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungho/project/UMSL/CS6420/project1/operator.cpp > CMakeFiles/p.dir/operator.cpp.i

CMakeFiles/p.dir/operator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p.dir/operator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungho/project/UMSL/CS6420/project1/operator.cpp -o CMakeFiles/p.dir/operator.cpp.s

CMakeFiles/p.dir/porter_duff.cpp.o: CMakeFiles/p.dir/flags.make
CMakeFiles/p.dir/porter_duff.cpp.o: ../porter_duff.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/seungho/project/UMSL/CS6420/project1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/p.dir/porter_duff.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p.dir/porter_duff.cpp.o -c /home/seungho/project/UMSL/CS6420/project1/porter_duff.cpp

CMakeFiles/p.dir/porter_duff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p.dir/porter_duff.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/seungho/project/UMSL/CS6420/project1/porter_duff.cpp > CMakeFiles/p.dir/porter_duff.cpp.i

CMakeFiles/p.dir/porter_duff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p.dir/porter_duff.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/seungho/project/UMSL/CS6420/project1/porter_duff.cpp -o CMakeFiles/p.dir/porter_duff.cpp.s

# Object files for target p
p_OBJECTS = \
"CMakeFiles/p.dir/operator.cpp.o" \
"CMakeFiles/p.dir/porter_duff.cpp.o"

# External object files for target p
p_EXTERNAL_OBJECTS =

p : CMakeFiles/p.dir/operator.cpp.o
p : CMakeFiles/p.dir/porter_duff.cpp.o
p : CMakeFiles/p.dir/build.make
p : CMakeFiles/p.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/seungho/project/UMSL/CS6420/project1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable p"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p.dir/build: p

.PHONY : CMakeFiles/p.dir/build

CMakeFiles/p.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p.dir/clean

CMakeFiles/p.dir/depend:
	cd /home/seungho/project/UMSL/CS6420/project1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/seungho/project/UMSL/CS6420/project1 /home/seungho/project/UMSL/CS6420/project1 /home/seungho/project/UMSL/CS6420/project1/cmake-build-debug /home/seungho/project/UMSL/CS6420/project1/cmake-build-debug /home/seungho/project/UMSL/CS6420/project1/cmake-build-debug/CMakeFiles/p.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p.dir/depend

