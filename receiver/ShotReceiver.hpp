#pragma once

#include "ShotData.hpp"
#include <string> 

class ShotReceiver {
public: 
    ShotReceiver() = default; 

    /**
     * @brief Processes a raw UDP packet. 
     * Pass this to UDPReceiver as the callback
     */
    void onPacket(const uint8_t* data, size_t length); 

private: 
    bool validate(const ShotData& shot); 
    void process(const ShotData& shot); 
};