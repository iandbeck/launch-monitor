#include "UdpReceiver.hpp"
#include "ShotReceiver.hpp"
#include "SerialReader.hpp"

#include <iostream>
#include <string>
#include <thread>

int main() {

    try {
        ShotReceiver shotReceiver; 

        // Create UDP receiver on port 5005, passing received packets to shotReceiver
        UdpReceiver udpReceiver(5005, [&shotReceiver](const uint8_t* data, size_t length) {
            shotReceiver.onPacket(data, length); 
        });
        // Start UDP thread
        std::thread udpThread([&udpReceiver] {
            udpReceiver.start();
        }); 

        SerialReader serialReader; 
        // Start Serial thread
        std::thread serialThread([&serialReader] {
            serialReader.start("/dev/ttyACM0");
        });

        // Wait for threads to finish
        udpThread.join();
        serialThread.join(); 
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; 
        return 1; 
    }

    return 0;
}