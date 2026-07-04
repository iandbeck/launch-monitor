#include "ShotReceiver.hpp"

#include <iostream>
#include <cstring>

void ShotReceiver::onPacket(const uint8_t data[UdpReceiver::RX_BUFFER_SIZE], size_t length)
{
    process(data, length);
}

void ShotReceiver::process(const uint8_t data[UdpReceiver::RX_BUFFER_SIZE], size_t length)
{
}
