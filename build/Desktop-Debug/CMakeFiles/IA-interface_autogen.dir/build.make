# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/facu/IA-interface

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/facu/IA-interface/build/Desktop-Debug

# Utility rule file for IA-interface_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/IA-interface_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/IA-interface_autogen.dir/progress.make

CMakeFiles/IA-interface_autogen: IA-interface_autogen/timestamp

IA-interface_autogen/timestamp: /usr/lib/qt6/moc
IA-interface_autogen/timestamp: /usr/lib/qt6/uic
IA-interface_autogen/timestamp: CMakeFiles/IA-interface_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/facu/IA-interface/build/Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target IA-interface"
	/usr/bin/cmake -E cmake_autogen /home/facu/IA-interface/build/Desktop-Debug/CMakeFiles/IA-interface_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/facu/IA-interface/build/Desktop-Debug/IA-interface_autogen/timestamp

IA-interface_autogen: CMakeFiles/IA-interface_autogen
IA-interface_autogen: IA-interface_autogen/timestamp
IA-interface_autogen: CMakeFiles/IA-interface_autogen.dir/build.make
.PHONY : IA-interface_autogen

# Rule to build all files generated by this target.
CMakeFiles/IA-interface_autogen.dir/build: IA-interface_autogen
.PHONY : CMakeFiles/IA-interface_autogen.dir/build

CMakeFiles/IA-interface_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/IA-interface_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/IA-interface_autogen.dir/clean

CMakeFiles/IA-interface_autogen.dir/depend:
	cd /home/facu/IA-interface/build/Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/facu/IA-interface /home/facu/IA-interface /home/facu/IA-interface/build/Desktop-Debug /home/facu/IA-interface/build/Desktop-Debug /home/facu/IA-interface/build/Desktop-Debug/CMakeFiles/IA-interface_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/IA-interface_autogen.dir/depend

