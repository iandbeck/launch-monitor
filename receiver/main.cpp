#include "UDPReceiver.hpp"

#include <iostream>
#include <string>

int main() {
    
    try {
        UDPReceiver receiver(5005, [](const std::string& data) {
            std::cout << "Got: " << data << std::endl;
        });
        receiver.start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; 
        return 1; 
    }

    return 0;
}