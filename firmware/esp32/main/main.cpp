#include <stdio.h>
#include <string> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WiFiManager.hpp"
#include "UDPSender.hpp"
#include "esp_wifi.h"
#include "sdkconfig.h"

#define UDP_PORT 5005

extern "C" void app_main() {
    // Connect to WiFi - blocks until IP assigned
    WiFiManager::connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);

    // Create sender targeting receiver
    UDPSender sender(CONFIG_MAC_IP, UDP_PORT); 

    int shot_count = 0;
    while (true) {
        std::string packet = "{\"module\": 1, \"ball_speed_mph\": 147.3, \"shot\": " + std::to_string(shot_count++) + "}";
        sender.send(packet); 
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}