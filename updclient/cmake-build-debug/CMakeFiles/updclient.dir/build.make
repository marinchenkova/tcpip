# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Programs\CLion 2016.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Programs\CLion 2016.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Users\Valentin\CLionProjects\tcpip_git\updclient

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/updclient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/updclient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/updclient.dir/flags.make

CMakeFiles/updclient.dir/main.cpp.obj: CMakeFiles/updclient.dir/flags.make
CMakeFiles/updclient.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/updclient.dir/main.cpp.obj"
	D:\Programming\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\updclient.dir\main.cpp.obj -c D:\Users\Valentin\CLionProjects\tcpip_git\updclient\main.cpp

CMakeFiles/updclient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/updclient.dir/main.cpp.i"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Users\Valentin\CLionProjects\tcpip_git\updclient\main.cpp > CMakeFiles\updclient.dir\main.cpp.i

CMakeFiles/updclient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/updclient.dir/main.cpp.s"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Users\Valentin\CLionProjects\tcpip_git\updclient\main.cpp -o CMakeFiles\updclient.dir\main.cpp.s

CMakeFiles/updclient.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/updclient.dir/main.cpp.obj.requires

CMakeFiles/updclient.dir/main.cpp.obj.provides: CMakeFiles/updclient.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\updclient.dir\build.make CMakeFiles/updclient.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/updclient.dir/main.cpp.obj.provides

CMakeFiles/updclient.dir/main.cpp.obj.provides.build: CMakeFiles/updclient.dir/main.cpp.obj


CMakeFiles/updclient.dir/Command.cpp.obj: CMakeFiles/updclient.dir/flags.make
CMakeFiles/updclient.dir/Command.cpp.obj: ../Command.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/updclient.dir/Command.cpp.obj"
	D:\Programming\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\updclient.dir\Command.cpp.obj -c D:\Users\Valentin\CLionProjects\tcpip_git\updclient\Command.cpp

CMakeFiles/updclient.dir/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/updclient.dir/Command.cpp.i"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Users\Valentin\CLionProjects\tcpip_git\updclient\Command.cpp > CMakeFiles\updclient.dir\Command.cpp.i

CMakeFiles/updclient.dir/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/updclient.dir/Command.cpp.s"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Users\Valentin\CLionProjects\tcpip_git\updclient\Command.cpp -o CMakeFiles\updclient.dir\Command.cpp.s

CMakeFiles/updclient.dir/Command.cpp.obj.requires:

.PHONY : CMakeFiles/updclient.dir/Command.cpp.obj.requires

CMakeFiles/updclient.dir/Command.cpp.obj.provides: CMakeFiles/updclient.dir/Command.cpp.obj.requires
	$(MAKE) -f CMakeFiles\updclient.dir\build.make CMakeFiles/updclient.dir/Command.cpp.obj.provides.build
.PHONY : CMakeFiles/updclient.dir/Command.cpp.obj.provides

CMakeFiles/updclient.dir/Command.cpp.obj.provides.build: CMakeFiles/updclient.dir/Command.cpp.obj


# Object files for target updclient
updclient_OBJECTS = \
"CMakeFiles/updclient.dir/main.cpp.obj" \
"CMakeFiles/updclient.dir/Command.cpp.obj"

# External object files for target updclient
updclient_EXTERNAL_OBJECTS =

updclient.exe: CMakeFiles/updclient.dir/main.cpp.obj
updclient.exe: CMakeFiles/updclient.dir/Command.cpp.obj
updclient.exe: CMakeFiles/updclient.dir/build.make
updclient.exe: CMakeFiles/updclient.dir/linklibs.rsp
updclient.exe: CMakeFiles/updclient.dir/objects1.rsp
updclient.exe: CMakeFiles/updclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable updclient.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\updclient.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/updclient.dir/build: updclient.exe

.PHONY : CMakeFiles/updclient.dir/build

CMakeFiles/updclient.dir/requires: CMakeFiles/updclient.dir/main.cpp.obj.requires
CMakeFiles/updclient.dir/requires: CMakeFiles/updclient.dir/Command.cpp.obj.requires

.PHONY : CMakeFiles/updclient.dir/requires

CMakeFiles/updclient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\updclient.dir\cmake_clean.cmake
.PHONY : CMakeFiles/updclient.dir/clean

CMakeFiles/updclient.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Users\Valentin\CLionProjects\tcpip_git\updclient D:\Users\Valentin\CLionProjects\tcpip_git\updclient D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug D:\Users\Valentin\CLionProjects\tcpip_git\updclient\cmake-build-debug\CMakeFiles\updclient.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/updclient.dir/depend

