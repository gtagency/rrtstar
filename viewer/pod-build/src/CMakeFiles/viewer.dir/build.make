# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/2.8.10.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/2.8.10.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/Cellar/cmake/2.8.10.2/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build

# Include any dependencies generated for this target.
include src/CMakeFiles/viewer.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/viewer.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/viewer.dir/flags.make

src/CMakeFiles/viewer.dir/main_viewer.cpp.o: src/CMakeFiles/viewer.dir/flags.make
src/CMakeFiles/viewer.dir/main_viewer.cpp.o: ../src/main_viewer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/viewer.dir/main_viewer.cpp.o"
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/viewer.dir/main_viewer.cpp.o -c /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/src/main_viewer.cpp

src/CMakeFiles/viewer.dir/main_viewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/viewer.dir/main_viewer.cpp.i"
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/src/main_viewer.cpp > CMakeFiles/viewer.dir/main_viewer.cpp.i

src/CMakeFiles/viewer.dir/main_viewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/viewer.dir/main_viewer.cpp.s"
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/src/main_viewer.cpp -o CMakeFiles/viewer.dir/main_viewer.cpp.s

src/CMakeFiles/viewer.dir/main_viewer.cpp.o.requires:
.PHONY : src/CMakeFiles/viewer.dir/main_viewer.cpp.o.requires

src/CMakeFiles/viewer.dir/main_viewer.cpp.o.provides: src/CMakeFiles/viewer.dir/main_viewer.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/viewer.dir/build.make src/CMakeFiles/viewer.dir/main_viewer.cpp.o.provides.build
.PHONY : src/CMakeFiles/viewer.dir/main_viewer.cpp.o.provides

src/CMakeFiles/viewer.dir/main_viewer.cpp.o.provides.build: src/CMakeFiles/viewer.dir/main_viewer.cpp.o

# Object files for target viewer
viewer_OBJECTS = \
"CMakeFiles/viewer.dir/main_viewer.cpp.o"

# External object files for target viewer
viewer_EXTERNAL_OBJECTS =

bin/viewer: src/CMakeFiles/viewer.dir/main_viewer.cpp.o
bin/viewer: src/CMakeFiles/viewer.dir/build.make
bin/viewer: src/CMakeFiles/viewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../bin/viewer"
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/viewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/viewer.dir/build: bin/viewer
.PHONY : src/CMakeFiles/viewer.dir/build

src/CMakeFiles/viewer.dir/requires: src/CMakeFiles/viewer.dir/main_viewer.cpp.o.requires
.PHONY : src/CMakeFiles/viewer.dir/requires

src/CMakeFiles/viewer.dir/clean:
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src && $(CMAKE_COMMAND) -P CMakeFiles/viewer.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/viewer.dir/clean

src/CMakeFiles/viewer.dir/depend:
	cd /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/src /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src /Users/thejenix/Dropbox/School/Agency/dev/rrtstar/viewer/pod-build/src/CMakeFiles/viewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/viewer.dir/depend

