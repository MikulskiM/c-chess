#!/bin/bash

# Remove old CMake configuration files
echo "Removing old CMake configuration files..."
if [ -d "build" ]; then
  rm -rf build/*
else
  mkdir build
fi

# Navigate to the build directory
cd build

# Detect the operating system and run the appropriate CMake command
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
  echo "Configuring for Windows..."
  cmake -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM=/d/MinGW/bin/make ..
else
  echo "Configuring for Linux..."
  cmake ..
fi

# Build the project
cmake --build .

# Check if the build was successful
if [ $? -eq 0 ]; then
  echo "Build succeeded, running the program..."
  # Run the program
  ./c_chess
else
  echo "Build failed, not running the program."
fi

# Return to the root directory
cd ..

# Pause on Windows systems
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
  read -p "Press any key to exit..."
fi
