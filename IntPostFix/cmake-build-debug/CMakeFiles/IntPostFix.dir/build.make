# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/IntPostFix.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/IntPostFix.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/IntPostFix.dir/flags.make

CMakeFiles/IntPostFix.dir/main.cpp.obj: CMakeFiles/IntPostFix.dir/flags.make
CMakeFiles/IntPostFix.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/IntPostFix.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\IntPostFix.dir\main.cpp.obj -c "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\main.cpp"

CMakeFiles/IntPostFix.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/IntPostFix.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\main.cpp" > CMakeFiles\IntPostFix.dir\main.cpp.i

CMakeFiles/IntPostFix.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/IntPostFix.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\main.cpp" -o CMakeFiles\IntPostFix.dir\main.cpp.s

CMakeFiles/IntPostFix.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/IntPostFix.dir/main.cpp.obj.requires

CMakeFiles/IntPostFix.dir/main.cpp.obj.provides: CMakeFiles/IntPostFix.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\IntPostFix.dir\build.make CMakeFiles/IntPostFix.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/IntPostFix.dir/main.cpp.obj.provides

CMakeFiles/IntPostFix.dir/main.cpp.obj.provides.build: CMakeFiles/IntPostFix.dir/main.cpp.obj


# Object files for target IntPostFix
IntPostFix_OBJECTS = \
"CMakeFiles/IntPostFix.dir/main.cpp.obj"

# External object files for target IntPostFix
IntPostFix_EXTERNAL_OBJECTS =

IntPostFix.exe: CMakeFiles/IntPostFix.dir/main.cpp.obj
IntPostFix.exe: CMakeFiles/IntPostFix.dir/build.make
IntPostFix.exe: CMakeFiles/IntPostFix.dir/linklibs.rsp
IntPostFix.exe: CMakeFiles/IntPostFix.dir/objects1.rsp
IntPostFix.exe: CMakeFiles/IntPostFix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable IntPostFix.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\IntPostFix.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/IntPostFix.dir/build: IntPostFix.exe

.PHONY : CMakeFiles/IntPostFix.dir/build

CMakeFiles/IntPostFix.dir/requires: CMakeFiles/IntPostFix.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/IntPostFix.dir/requires

CMakeFiles/IntPostFix.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\IntPostFix.dir\cmake_clean.cmake
.PHONY : CMakeFiles/IntPostFix.dir/clean

CMakeFiles/IntPostFix.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix" "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix" "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug" "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug" "C:\Users\Mirela\Desktop\ALGORITMI I STRUKTURE PODATAKA\Knjiga\IntPostFix\cmake-build-debug\CMakeFiles\IntPostFix.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/IntPostFix.dir/depend

