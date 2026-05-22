#!/bin/bash

# Exit immediately if any command fails 
set -e 

# Get current directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/_build"

# Create build directory if it doesn't exist 
mkdir -p "$BUILD_DIR"

# Configure and build
cd "$BUILD_DIR"
cmake ..
make

echo "Build complete!"