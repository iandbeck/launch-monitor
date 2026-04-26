# Define executable and its source files
add_executable(launch_monitor_receiver
    main.cpp
    UDPReceiver.cpp
)

target_include_directories(launch_monitor_receiver PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(launch_monitor_receiver PRIVATE 
    -Wall
    -Wextra
    -Wpedantic
)
