# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Check the operating system and set compilers for Windows
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # Set C and C++ compilers manually for Windows
    set(CMAKE_C_COMPILER "D:/MinGW/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "D:/MinGW/bin/g++.exe")
endif()

# Project name and version
project(c_chess VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add all header files from the include directory
include_directories(include)

# Set of all source files
set(SOURCES
    src/main.c
    src/player.c
    src/board.c
)

# Add the executable
add_executable(c_chess ${SOURCES})
