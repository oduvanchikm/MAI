# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/passwd/MAI/mp/lab4/n_9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/passwd/MAI/mp/lab4/n_9/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/n_9.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/n_9.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/n_9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/n_9.dir/flags.make

CMakeFiles/n_9.dir/main.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/main.c.o: /home/passwd/MAI/mp/lab4/n_9/main.c
CMakeFiles/n_9.dir/main.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/n_9.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/main.c.o -MF CMakeFiles/n_9.dir/main.c.o.d -o CMakeFiles/n_9.dir/main.c.o -c /home/passwd/MAI/mp/lab4/n_9/main.c

CMakeFiles/n_9.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/main.c > CMakeFiles/n_9.dir/main.c.i

CMakeFiles/n_9.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/main.c -o CMakeFiles/n_9.dir/main.c.s

CMakeFiles/n_9.dir/heaps/binary_heap.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/heaps/binary_heap.c.o: /home/passwd/MAI/mp/lab4/n_9/heaps/binary_heap.c
CMakeFiles/n_9.dir/heaps/binary_heap.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/n_9.dir/heaps/binary_heap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/heaps/binary_heap.c.o -MF CMakeFiles/n_9.dir/heaps/binary_heap.c.o.d -o CMakeFiles/n_9.dir/heaps/binary_heap.c.o -c /home/passwd/MAI/mp/lab4/n_9/heaps/binary_heap.c

CMakeFiles/n_9.dir/heaps/binary_heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/heaps/binary_heap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/heaps/binary_heap.c > CMakeFiles/n_9.dir/heaps/binary_heap.c.i

CMakeFiles/n_9.dir/heaps/binary_heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/heaps/binary_heap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/heaps/binary_heap.c -o CMakeFiles/n_9.dir/heaps/binary_heap.c.s

CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o: /home/passwd/MAI/mp/lab4/n_9/heaps/fibonacci_heap.c
CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o -MF CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o.d -o CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o -c /home/passwd/MAI/mp/lab4/n_9/heaps/fibonacci_heap.c

CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/heaps/fibonacci_heap.c > CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.i

CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/heaps/fibonacci_heap.c -o CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.s

CMakeFiles/n_9.dir/heaps/binomial_heap.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/heaps/binomial_heap.c.o: /home/passwd/MAI/mp/lab4/n_9/heaps/binomial_heap.c
CMakeFiles/n_9.dir/heaps/binomial_heap.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/n_9.dir/heaps/binomial_heap.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/heaps/binomial_heap.c.o -MF CMakeFiles/n_9.dir/heaps/binomial_heap.c.o.d -o CMakeFiles/n_9.dir/heaps/binomial_heap.c.o -c /home/passwd/MAI/mp/lab4/n_9/heaps/binomial_heap.c

CMakeFiles/n_9.dir/heaps/binomial_heap.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/heaps/binomial_heap.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/heaps/binomial_heap.c > CMakeFiles/n_9.dir/heaps/binomial_heap.c.i

CMakeFiles/n_9.dir/heaps/binomial_heap.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/heaps/binomial_heap.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/heaps/binomial_heap.c -o CMakeFiles/n_9.dir/heaps/binomial_heap.c.s

CMakeFiles/n_9.dir/storages/hash_set.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/storages/hash_set.c.o: /home/passwd/MAI/mp/lab4/n_9/storages/hash_set.c
CMakeFiles/n_9.dir/storages/hash_set.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/n_9.dir/storages/hash_set.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/storages/hash_set.c.o -MF CMakeFiles/n_9.dir/storages/hash_set.c.o.d -o CMakeFiles/n_9.dir/storages/hash_set.c.o -c /home/passwd/MAI/mp/lab4/n_9/storages/hash_set.c

CMakeFiles/n_9.dir/storages/hash_set.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/storages/hash_set.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/storages/hash_set.c > CMakeFiles/n_9.dir/storages/hash_set.c.i

CMakeFiles/n_9.dir/storages/hash_set.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/storages/hash_set.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/storages/hash_set.c -o CMakeFiles/n_9.dir/storages/hash_set.c.s

CMakeFiles/n_9.dir/storages/binary_search_tree.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/storages/binary_search_tree.c.o: /home/passwd/MAI/mp/lab4/n_9/storages/binary_search_tree.c
CMakeFiles/n_9.dir/storages/binary_search_tree.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/n_9.dir/storages/binary_search_tree.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/storages/binary_search_tree.c.o -MF CMakeFiles/n_9.dir/storages/binary_search_tree.c.o.d -o CMakeFiles/n_9.dir/storages/binary_search_tree.c.o -c /home/passwd/MAI/mp/lab4/n_9/storages/binary_search_tree.c

CMakeFiles/n_9.dir/storages/binary_search_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/storages/binary_search_tree.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/storages/binary_search_tree.c > CMakeFiles/n_9.dir/storages/binary_search_tree.c.i

CMakeFiles/n_9.dir/storages/binary_search_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/storages/binary_search_tree.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/storages/binary_search_tree.c -o CMakeFiles/n_9.dir/storages/binary_search_tree.c.s

CMakeFiles/n_9.dir/storages/dynamic_array.c.o: CMakeFiles/n_9.dir/flags.make
CMakeFiles/n_9.dir/storages/dynamic_array.c.o: /home/passwd/MAI/mp/lab4/n_9/storages/dynamic_array.c
CMakeFiles/n_9.dir/storages/dynamic_array.c.o: CMakeFiles/n_9.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/n_9.dir/storages/dynamic_array.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/n_9.dir/storages/dynamic_array.c.o -MF CMakeFiles/n_9.dir/storages/dynamic_array.c.o.d -o CMakeFiles/n_9.dir/storages/dynamic_array.c.o -c /home/passwd/MAI/mp/lab4/n_9/storages/dynamic_array.c

CMakeFiles/n_9.dir/storages/dynamic_array.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/n_9.dir/storages/dynamic_array.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/passwd/MAI/mp/lab4/n_9/storages/dynamic_array.c > CMakeFiles/n_9.dir/storages/dynamic_array.c.i

CMakeFiles/n_9.dir/storages/dynamic_array.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/n_9.dir/storages/dynamic_array.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/passwd/MAI/mp/lab4/n_9/storages/dynamic_array.c -o CMakeFiles/n_9.dir/storages/dynamic_array.c.s

# Object files for target n_9
n_9_OBJECTS = \
"CMakeFiles/n_9.dir/main.c.o" \
"CMakeFiles/n_9.dir/heaps/binary_heap.c.o" \
"CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o" \
"CMakeFiles/n_9.dir/heaps/binomial_heap.c.o" \
"CMakeFiles/n_9.dir/storages/hash_set.c.o" \
"CMakeFiles/n_9.dir/storages/binary_search_tree.c.o" \
"CMakeFiles/n_9.dir/storages/dynamic_array.c.o"

# External object files for target n_9
n_9_EXTERNAL_OBJECTS =

n_9: CMakeFiles/n_9.dir/main.c.o
n_9: CMakeFiles/n_9.dir/heaps/binary_heap.c.o
n_9: CMakeFiles/n_9.dir/heaps/fibonacci_heap.c.o
n_9: CMakeFiles/n_9.dir/heaps/binomial_heap.c.o
n_9: CMakeFiles/n_9.dir/storages/hash_set.c.o
n_9: CMakeFiles/n_9.dir/storages/binary_search_tree.c.o
n_9: CMakeFiles/n_9.dir/storages/dynamic_array.c.o
n_9: CMakeFiles/n_9.dir/build.make
n_9: CMakeFiles/n_9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C executable n_9"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/n_9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/n_9.dir/build: n_9
.PHONY : CMakeFiles/n_9.dir/build

CMakeFiles/n_9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/n_9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/n_9.dir/clean

CMakeFiles/n_9.dir/depend:
	cd /home/passwd/MAI/mp/lab4/n_9/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/passwd/MAI/mp/lab4/n_9 /home/passwd/MAI/mp/lab4/n_9 /home/passwd/MAI/mp/lab4/n_9/cmake-build-debug /home/passwd/MAI/mp/lab4/n_9/cmake-build-debug /home/passwd/MAI/mp/lab4/n_9/cmake-build-debug/CMakeFiles/n_9.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/n_9.dir/depend

