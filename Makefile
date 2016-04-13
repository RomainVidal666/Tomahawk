# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thomas/Documents/Development/Tomahawk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomas/Documents/Development/Tomahawk

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Documents/Development/Tomahawk/CMakeFiles /home/thomas/Documents/Development/Tomahawk/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thomas/Documents/Development/Tomahawk/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named tomahawk

# Build rule for target.
tomahawk: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 tomahawk
.PHONY : tomahawk

# fast build rule for target.
tomahawk/fast:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/build
.PHONY : tomahawk/fast

# target to build an object file
src/api.o:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/api.o
.PHONY : src/api.o

# target to preprocess a source file
src/api.i:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/api.i
.PHONY : src/api.i

# target to generate assembly for a file
src/api.s:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/api.s
.PHONY : src/api.s

# target to build an object file
src/http_node.o:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_node.o
.PHONY : src/http_node.o

# target to preprocess a source file
src/http_node.i:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_node.i
.PHONY : src/http_node.i

# target to generate assembly for a file
src/http_node.s:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_node.s
.PHONY : src/http_node.s

# target to build an object file
src/http_parser.o:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_parser.o
.PHONY : src/http_parser.o

# target to preprocess a source file
src/http_parser.i:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_parser.i
.PHONY : src/http_parser.i

# target to generate assembly for a file
src/http_parser.s:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_parser.s
.PHONY : src/http_parser.s

# target to build an object file
src/http_response.o:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_response.o
.PHONY : src/http_response.o

# target to preprocess a source file
src/http_response.i:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_response.i
.PHONY : src/http_response.i

# target to generate assembly for a file
src/http_response.s:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/http_response.s
.PHONY : src/http_response.s

# target to build an object file
src/main.o:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/main.o
.PHONY : src/main.o

# target to preprocess a source file
src/main.i:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/main.i
.PHONY : src/main.i

# target to generate assembly for a file
src/main.s:
	$(MAKE) -f CMakeFiles/tomahawk.dir/build.make CMakeFiles/tomahawk.dir/src/main.s
.PHONY : src/main.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... tomahawk"
	@echo "... src/api.o"
	@echo "... src/api.i"
	@echo "... src/api.s"
	@echo "... src/http_node.o"
	@echo "... src/http_node.i"
	@echo "... src/http_node.s"
	@echo "... src/http_parser.o"
	@echo "... src/http_parser.i"
	@echo "... src/http_parser.s"
	@echo "... src/http_response.o"
	@echo "... src/http_response.i"
	@echo "... src/http_response.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

