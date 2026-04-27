#include "Utils.hpp"

#include <stdio.h>
#include <string> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "WiFiManager.hpp"
#include "UDPSender.hpp"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_log.h"

void Utils::ScanForNetworks()
{
    nvs_flash_init(); 
    esp_netif_init(); 
    esp_event_loop_create_default(); 
    esp_netif_create_default_wifi_sta(); 

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); 
    esp_wifi_init(&cfg); 

    wifi_scan_config_t scan_config = {}; 
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start(); 
    esp_wifi_scan_start(&scan_config, true); 

    uint16_t ap_count = 0; 
    esp_wifi_scan_get_ap_num(&ap_count);

    wifi_ap_record_t ap_list[20];
    esp_wifi_scan_get_ap_records(&ap_count, ap_list); 

    for (int i = 0; i < ap_count; i++) {
        ESP_LOGI("SCAN", "SSID: %s, RSSI: %d", ap_list[i].ssid, ap_list[i].rssi); 
    }
}