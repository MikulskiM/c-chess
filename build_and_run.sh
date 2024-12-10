#!/bin/bash

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
  mkdir build
fi

# Navigate to the build directory
cd build

# Run CMake to configure the project
cmake ..

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
