#pragma once 

#include <string> 
#include <functional>

/**
 * @brief Listens on a UDP port and dispatches incoming packets to a callback.
 *
 * UDPReceiver opens a non-blocking UDP socket on construction and provides
 * a blocking start() loop that fires a user-supplied callback for each
 * packet received. Intended as the transport layer for radar shot data
 * from ESP32 sensor nodes.
 *
 * @note Not thread-safe. start() blocks the calling thread indefinitely.
 */

class UDPReceiver {
public: 
    using PacketCallback = std::function<void(const uint8_t*, size_t)>;

    /**
     * @brief Constructs the receiver and binds to the given port.
     * @param port      UDP port to listen on.
     * @param callback  Function called with raw packet data on each receive.
     * @throws std::runtime_error if socket creation or bind fails.
     */
    UDPReceiver(int port, PacketCallback callback); 
    ~UDPReceiver(); 

    /** 
     * @brief Blocks forever, calling the callback for each incoming packet.
     */
    void start(); 

private: 
    void receive(); 

    int port_;
    int sock_;
    PacketCallback callback_; 

    // Fixed size stack buffer
    static constexpr size_t BUFFER_SIZE = 256;
    uint8_t buffer_[BUFFER_SIZE];
};