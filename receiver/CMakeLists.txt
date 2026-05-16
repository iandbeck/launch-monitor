# Define executable and its source files
add_executable(launch_monitor_receiver
    src/main.cpp
    src/ShotReceiver.cpp
    src/UdpReceiver.cpp
)

target_include_directories(launch_monitor_receiver PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/common
)

target_compile_options(launch_monitor_receiver PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
