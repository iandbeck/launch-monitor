#include "UdpReceiver.hpp"
#include "ShotReceiver.hpp"

#include <iostream>
#include <string>

int main() {

    try {
        ShotReceiver shotReceiver; 

        UDPReceiver udpReceiver(5005, [&shotReceiver](const uint8_t* data, size_t length) {
            shotReceiver.onPacket(data, length); 
        });
        udpReceiver.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; 
        return 1; 
    }

    return 0;
}