#pragma once

#include <cstdint>

struct ShotData {
    float ball_speed_mph_1; // Module 1 raw reading
    float ball_speed_mph_2; // Module 2 raw reading
    uint32_t timestamp_ms;  // Time of shot 
    uint8_t valid;          // Validity of data 
} __attribute__((packed));