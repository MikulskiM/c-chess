# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(c_chess VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(c_chess main.c board.c player.c)
