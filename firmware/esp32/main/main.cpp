#include "UartDriver.hpp"
#include "UdpSender.hpp"
#include "WiFiManager.hpp"
#include "esp_log.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>
#include <string>

// TODO: Move these to a configuration file
static constexpr int UDP_PORT = 5005;
static constexpr int RADAR_BAUD_RATE = 230400;

extern "C" void app_main()
{
    // Supress phy comm logs for debug
    esp_log_level_set("phy_comm", ESP_LOG_NONE);

    // Connect to WiFi - blocks until IP assigned
    WiFiManager::connect(CONFIG_WIFI_SSID, CONFIG_WIFI_PASSWORD);

    // Create sender targeting receiver
    UdpSender sender(CONFIG_MAC_IP, UDP_PORT);

    // Start UART receive task from radar module
    UartDriver uartDriver(RADAR_BAUD_RATE, &sender);
    uartDriver.startRxTask();

    // Configure esp and send rolling buffer trigger
    uartDriver.sendCommand("PA");
    vTaskDelay(pdMS_TO_TICKS(3000));
    uartDriver.triggerPulse();

    while (true)
    {
        vTaskDelay(portMAX_DELAY);
    }
}