# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shkwon_ug/tmp/tmp.eyv3ldFFuv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu

# Include any dependencies generated for this target.
include submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/compiler_depend.make

# Include the progress variables for this target.
include submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/progress.make

# Include the compile flags for this target's objects.
include submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/flags.make

submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o: submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/flags.make
submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o: /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lefzlib/lefzlib.cpp
submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o: submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o"
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o -MF CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o.d -o CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o -c /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lefzlib/lefzlib.cpp

submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.i"
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lefzlib/lefzlib.cpp > CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.i

submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.s"
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lefzlib/lefzlib.cpp -o CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.s

# Object files for target lefzlib
lefzlib_OBJECTS = \
"CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o"

# External object files for target lefzlib
lefzlib_EXTERNAL_OBJECTS =

/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a: submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/lefzlib/lefzlib.cpp.o
/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a: submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/build.make
/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a: submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a"
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && $(CMAKE_COMMAND) -P CMakeFiles/lefzlib.dir/cmake_clean_target.cmake
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lefzlib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/build: /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027/lib/liblefzlib.a
.PHONY : submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/build

submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/clean:
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 && $(CMAKE_COMMAND) -P CMakeFiles/lefzlib.dir/cmake_clean.cmake
.PHONY : submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/clean

submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/depend:
	cd /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shkwon_ug/tmp/tmp.eyv3ldFFuv /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/submodule/OpenDP/module/lef/5.8-p027 /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027 /home/shkwon_ug/tmp/tmp.eyv3ldFFuv/cmake-build-debug-csdl_ubuntu/submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : submodule/OpenDP/module/lef/5.8-p027/CMakeFiles/lefzlib.dir/depend

