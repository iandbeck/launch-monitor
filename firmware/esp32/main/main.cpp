#include <stdio.h>
#include <string> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WiFiManager.hpp"
#include "UdpSender.hpp"
#include "esp_wifi.h"
#include "sdkconfig.h"
#include "UartDriver.hpp"

// For testing
#include "ShotData.hpp"
#include "esp_random.h"
#include "esp_timer.h"

// TODO: Move these to a configuration file
#define UDP_PORT 5005
#define RADAR_BAUD_RATE 19200

extern "C" void app_main() {
    // Connect to WiFi - blocks until IP assigned
    // WiFiManager::connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);

    // Create sender targeting receiver
    // UdpSender sender(CONFIG_MAC_IP, UDP_PORT); 

    // Start UART receive task from radar module
    UartDriver uart_config(RADAR_BAUD_RATE); 
    uart_config.init(); 
    uart_config.startRxTask(); 
}