cmake_minimum_required(VERSION 3.20)
project(LaunchMonitor VERSION 1.0 LANGUAGES CXX)

# Global C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(receiver)