#pragma once

#include <string>
#include <functional>
#include <cstdint>

/**
 * @brief Listens on a Udp port and dispatches incoming packets to a callback.
 *
 * UdpReceiver opens a non-blocking Udp socket on construction and provides
 * a blocking start() loop that fires a user-supplied callback for each
 * packet received. Intended as the transport layer for radar shot data
 * from ESP32 sensor nodes.
 *
 * @note Not thread-safe. start() blocks the calling thread indefinitely.
 */

class UdpReceiver
{
public:
    using PacketCallback = std::function<void(const uint8_t *, size_t)>;

    /**
     * @brief Constructs the receiver and binds to the given port.
     * @param port      Udp port to listen on.
     * @param callback  Function called with raw packet data on each receive.
     * @throws std::runtime_error if socket creation or bind fails.
     */
    UdpReceiver(int port, PacketCallback callback);
    ~UdpReceiver();

    /**
     * @brief Blocks forever, calling the callback for each incoming packet.
     */
    void start();

    static constexpr size_t RX_BUFFER_SIZE = 512;

private:
    void receive();

    int port_;
    int sock_;
    PacketCallback callback_;

    // Fixed size stack buffer
    uint8_t buffer_[RX_BUFFER_SIZE];
};