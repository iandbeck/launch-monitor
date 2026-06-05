#pragma once 

#include <string> 
#include <cstddef>

/** 
 * @brief Sends Udp packets to a remote host
 * Thin wrapper around lwIP's BSD socket API. 
 * Intended as the transport layer for golf 
 * data from the ESP32 to the receiver. 
 */
class UdpSender {
public: 
    /** 
     * @brief Constructs sender targeting the given host and port. 
     * @param   host    Destination IP address as a string e.g. "192.168.1.100"
     * @param   port    Destination Udp port
     */
    UdpSender(const std::string& host, int port);
    ~UdpSender(); 

    /**
     * @brief Sends a Udp payload. 
     * @param data  Payload to send.
     */
    void send(const uint8_t* data, size_t length);

private: 
    std::string host_; 
    int port_; 
    int sock_;
};