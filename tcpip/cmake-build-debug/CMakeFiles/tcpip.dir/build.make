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
CMAKE_SOURCE_DIR = D:\Users\Valentin\CLionProjects\tcpip_git\tcpip

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tcpip.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tcpip.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tcpip.dir/flags.make

CMakeFiles/tcpip.dir/main.cpp.obj: CMakeFiles/tcpip.dir/flags.make
CMakeFiles/tcpip.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tcpip.dir/main.cpp.obj"
	D:\Programming\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tcpip.dir\main.cpp.obj -c D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\main.cpp

CMakeFiles/tcpip.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpip.dir/main.cpp.i"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\main.cpp > CMakeFiles\tcpip.dir\main.cpp.i

CMakeFiles/tcpip.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpip.dir/main.cpp.s"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\main.cpp -o CMakeFiles\tcpip.dir\main.cpp.s

CMakeFiles/tcpip.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/tcpip.dir/main.cpp.obj.requires

CMakeFiles/tcpip.dir/main.cpp.obj.provides: CMakeFiles/tcpip.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\tcpip.dir\build.make CMakeFiles/tcpip.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/tcpip.dir/main.cpp.obj.provides

CMakeFiles/tcpip.dir/main.cpp.obj.provides.build: CMakeFiles/tcpip.dir/main.cpp.obj


CMakeFiles/tcpip.dir/Command.cpp.obj: CMakeFiles/tcpip.dir/flags.make
CMakeFiles/tcpip.dir/Command.cpp.obj: ../Command.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tcpip.dir/Command.cpp.obj"
	D:\Programming\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tcpip.dir\Command.cpp.obj -c D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Command.cpp

CMakeFiles/tcpip.dir/Command.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpip.dir/Command.cpp.i"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Command.cpp > CMakeFiles\tcpip.dir\Command.cpp.i

CMakeFiles/tcpip.dir/Command.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpip.dir/Command.cpp.s"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Command.cpp -o CMakeFiles\tcpip.dir\Command.cpp.s

CMakeFiles/tcpip.dir/Command.cpp.obj.requires:

.PHONY : CMakeFiles/tcpip.dir/Command.cpp.obj.requires

CMakeFiles/tcpip.dir/Command.cpp.obj.provides: CMakeFiles/tcpip.dir/Command.cpp.obj.requires
	$(MAKE) -f CMakeFiles\tcpip.dir\build.make CMakeFiles/tcpip.dir/Command.cpp.obj.provides.build
.PHONY : CMakeFiles/tcpip.dir/Command.cpp.obj.provides

CMakeFiles/tcpip.dir/Command.cpp.obj.provides.build: CMakeFiles/tcpip.dir/Command.cpp.obj


CMakeFiles/tcpip.dir/Client.cpp.obj: CMakeFiles/tcpip.dir/flags.make
CMakeFiles/tcpip.dir/Client.cpp.obj: ../Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tcpip.dir/Client.cpp.obj"
	D:\Programming\MinGW\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tcpip.dir\Client.cpp.obj -c D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Client.cpp

CMakeFiles/tcpip.dir/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpip.dir/Client.cpp.i"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Client.cpp > CMakeFiles\tcpip.dir\Client.cpp.i

CMakeFiles/tcpip.dir/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpip.dir/Client.cpp.s"
	D:\Programming\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\Client.cpp -o CMakeFiles\tcpip.dir\Client.cpp.s

CMakeFiles/tcpip.dir/Client.cpp.obj.requires:

.PHONY : CMakeFiles/tcpip.dir/Client.cpp.obj.requires

CMakeFiles/tcpip.dir/Client.cpp.obj.provides: CMakeFiles/tcpip.dir/Client.cpp.obj.requires
	$(MAKE) -f CMakeFiles\tcpip.dir\build.make CMakeFiles/tcpip.dir/Client.cpp.obj.provides.build
.PHONY : CMakeFiles/tcpip.dir/Client.cpp.obj.provides

CMakeFiles/tcpip.dir/Client.cpp.obj.provides.build: CMakeFiles/tcpip.dir/Client.cpp.obj


# Object files for target tcpip
tcpip_OBJECTS = \
"CMakeFiles/tcpip.dir/main.cpp.obj" \
"CMakeFiles/tcpip.dir/Command.cpp.obj" \
"CMakeFiles/tcpip.dir/Client.cpp.obj"

# External object files for target tcpip
tcpip_EXTERNAL_OBJECTS =

tcpip.exe: CMakeFiles/tcpip.dir/main.cpp.obj
tcpip.exe: CMakeFiles/tcpip.dir/Command.cpp.obj
tcpip.exe: CMakeFiles/tcpip.dir/Client.cpp.obj
tcpip.exe: CMakeFiles/tcpip.dir/build.make
tcpip.exe: CMakeFiles/tcpip.dir/linklibs.rsp
tcpip.exe: CMakeFiles/tcpip.dir/objects1.rsp
tcpip.exe: CMakeFiles/tcpip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tcpip.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tcpip.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tcpip.dir/build: tcpip.exe

.PHONY : CMakeFiles/tcpip.dir/build

CMakeFiles/tcpip.dir/requires: CMakeFiles/tcpip.dir/main.cpp.obj.requires
CMakeFiles/tcpip.dir/requires: CMakeFiles/tcpip.dir/Command.cpp.obj.requires
CMakeFiles/tcpip.dir/requires: CMakeFiles/tcpip.dir/Client.cpp.obj.requires

.PHONY : CMakeFiles/tcpip.dir/requires

CMakeFiles/tcpip.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tcpip.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tcpip.dir/clean

CMakeFiles/tcpip.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Users\Valentin\CLionProjects\tcpip_git\tcpip D:\Users\Valentin\CLionProjects\tcpip_git\tcpip D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug D:\Users\Valentin\CLionProjects\tcpip_git\tcpip\cmake-build-debug\CMakeFiles\tcpip.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tcpip.dir/depend
