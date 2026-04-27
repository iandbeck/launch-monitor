#pragma once 

#include <string> 
#include <cstddef>

/** 
 * @brief Sends UDP packets to a remote host
 * Thin wrapper around lwIP's BSD socket API. 
 * Intended as the transport layer for golf 
 * data from the ESP32 to the receiver. 
 */
class UDPSender {
public: 
    /** 
     * @brief Constructs sender targeting the given host and port. 
     * @param   host    Destination IP address as a string e.g. "192.168.1.100"
     * @param   port    Destination UDP port
     */
    UDPSender(const std::string& host, int port);
    ~UDPSender(); 

    /**
     * @brief Sends a UDP payload. 
     * @param data  Payload to send.
     */
    void send(const char* data, size_t length);

private: 
    std::string host_; 
    int port_; 
    int sock_;
};