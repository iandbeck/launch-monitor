# Define executable and its source files
add_executable(launch_monitor_receiver
    main.cpp
    UdpReceiver.cpp
    ShotReceiver.cpp
)

target_include_directories(launch_monitor_receiver PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/common
)

target_compile_options(launch_monitor_receiver PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
