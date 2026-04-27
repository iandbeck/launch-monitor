#include <stdio.h>
#include <string> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WiFiManager.hpp"
#include "UDPSender.hpp"
#include "esp_wifi.h"
#include "sdkconfig.h"

// For testing
#include "ShotData.hpp"
#include "esp_random.h"
#include "esp_timer.h"

#define UDP_PORT 5005

extern "C" void app_main() {
    // Connect to WiFi - blocks until IP assigned
    WiFiManager::connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);

    // Create sender targeting receiver
    UDPSender sender(CONFIG_MAC_IP, UDP_PORT); 


    auto random_float = [](float min, float max) -> float {
        return min + ((float)esp_random() / (float)UINT32_MAX) * (max - min); 
    };
    
    while (true) {
        ShotData mock_data{};
        mock_data.ball_speed_mph_1  = random_float(120.0f, 170.0f);
        mock_data.ball_speed_mph_2  = 0; 
        mock_data.timestamp_ms      = esp_timer_get_time() / 1000; 
        mock_data.valid             = 1; 

        sender.send(reinterpret_cast<const char*>(&mock_data), sizeof(ShotData)); 
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}