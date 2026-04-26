#include "UDPReceiver.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <functional>


// Constuctor
UDPReceiver::UDPReceiver(int port, PacketCallback callback) 
    : port_(port), sock_(-1), callback_(callback) {
    // Create UDP socket
    sock_ = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    // Configure address
    sockaddr_in addr;
    addr.sin_family         = AF_INET;
    addr.sin_port           = htons(port_);
    addr.sin_addr.s_addr    = INADDR_ANY;

    // Bind socket to port
    if (bind(sock_, (sockaddr *)&addr, sizeof(addr)) < 0) {
        close(sock_);
        throw std::runtime_error("Failed to bind socket to port" + std::to_string(port_));
    }
    std::cout << "Receiver listening on port " << port_ << std::endl;
}

UDPReceiver::~UDPReceiver() {
    if (sock_ >= 0) {
        close(sock_);
    }
}

void UDPReceiver::start() {
    while (true) {
        std::string packet = receive();
        callback_(packet); 
    }
}

// ** Currently deals only with strings, will change later ** 
std::string UDPReceiver::receive() {
    char buffer[1024];
    sockaddr_in sender{};
    socklen_t sender_len = sizeof(sender); 

    ssize_t bytes = recvfrom(sock_,
        buffer, 
        sizeof(buffer) - 1,
        0, 
        (sockaddr*)&sender,
        &sender_len);

    if (bytes < 0) {
        throw std::runtime_error("Failed to receive data on port " + std::to_string(port_));
    }

    buffer[bytes] = '\0';
    return std::string(buffer); 
}
