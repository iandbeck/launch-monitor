# Define executable and its source files
add_executable(processor
    src/main.cpp
    src/ShotReceiver.cpp
    src/UdpReceiver.cpp
    src/SerialReader.cpp
)

target_include_directories(processor PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/common
)

target_compile_options(processor PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
