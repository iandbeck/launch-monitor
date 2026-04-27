#include "ShotReceiver.hpp"
#include "ShotData.hpp"

#include <iostream> 

void ShotReceiver::onPacket(const uint8_t* data, size_t length) 
{
    if (length != sizeof(ShotData)) 
    {
        std::cerr << "Malformed packet: expected " << sizeof(ShotData) << "\nBytes received: " << length << std::endl;
        return;   
    }

    // Cast incoming data into ShotData struct
    ShotData shot{};
    std::memcpy(&shot, data, sizeof(ShotData));
    
    if (!validate(shot)) 
    {
        std::cerr << "Invalid shot data, discarding" << std::endl;
        return;
    }

    // Process shot data
    process(shot);
}

bool ShotReceiver::validate(const ShotData& shot) 
{
    if (!shot.valid) return false; 
    if (shot.ball_speed_mph_1 < 0.0f || shot.ball_speed_mph_1 > 220.0f) return false; 
    if (shot.ball_speed_mph_2 < 0.0f || shot.ball_speed_mph_2 > 220.0f) return false; 
    return true; 
}

void ShotReceiver::process(const ShotData& shot) 
{
    std::cout << "|------------------------------------------|" << std::endl;
    std::cout << "Ball speed 1      :   " << shot.ball_speed_mph_1 << std::endl;
    std::cout << "Ball speed 2      :   " << shot.ball_speed_mph_2 << std::endl;
    std::cout << "Timestamp (ms)    :   " << shot.timestamp_ms << std::endl;
    std::cout << "|------------------------------------------|" << std::endl;

}

