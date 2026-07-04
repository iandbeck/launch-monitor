#pragma once

#include "UdpReceiver.hpp"
#include <string>

class ShotReceiver
{
public:
    ShotReceiver() = default;

    /**
     * @brief Processes a raw UDP packet.
     * Pass this to UDPReceiver as the callback
     */
    void onPacket(const uint8_t *data, size_t length);

private:
    void process(const uint8_t *data, size_t length);
};