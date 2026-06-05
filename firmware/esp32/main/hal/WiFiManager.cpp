#include "WiFiManager.hpp"

#include <stdexcept> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "nvs_flash.h"

// Debug 
#include "Utils.hpp"

static const char* TAG = "WiFiManager";
static EventGroupHandle_t wifi_event_group; 
static const int CONNECTED_BIT = BIT0;

// Event handler for WiFi and IP events
static void event_handler(  void* arg, 
                            esp_event_base_t event_base, 
                            int32_t event_id, 
                            void* event_data    ) 
{
    ESP_LOGI(TAG, "Event: base=%s id=%ld", event_base, event_id);

    // Wifi Connect Event
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) 
    {
        ESP_LOGI(TAG, "STA started, connecting...");
        esp_wifi_connect(); 
    }
    // Wifi Disconnect Event
    else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) 
    { 
        wifi_event_sta_disconnected_t* event = (wifi_event_sta_disconnected_t*) event_data; 
        ESP_LOGW(TAG, "Disconnected: %d, retrying...", event->reason);
        esp_wifi_connect(); 
    } 
    // IP Assigned Event 
    else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP)
    {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data; 
        ESP_LOGI(TAG, "Got IP: " IPSTR, IP2STR(&event->ip_info.ip));
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
    }
}

void WiFiManager::connect(const std::string& ssid, const std::string& password) 
{ 
    // Initialize NVS - required for WiFi driver
    esp_err_t ret = nvs_flash_init(); 
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)  
    {
        nvs_flash_erase(); 
        nvs_flash_init(); 
    }

    // Initialize network interface and event loop
    esp_netif_init(); 
    esp_event_loop_create_default(); 
    esp_netif_create_default_wifi_sta(); 

    // Initialize WiFi with default config
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT(); 
    esp_wifi_init(&cfg); 

    // Create event group to block until connected
    wifi_event_group = xEventGroupCreate(); 

    // Register event handlers 
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL); 
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL); 

    // Configure WiFi credentials 
    wifi_config_t wifi_config = {};
    memcpy(wifi_config.sta.ssid, ssid.c_str(), ssid.size());
    memcpy(wifi_config.sta.password, password.c_str(), password.size());

    esp_wifi_set_mode(WIFI_MODE_STA); 
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config); 
    esp_wifi_start(); 

    // Start DHCP client
    esp_netif_t* netif = esp_netif_get_handle_from_ifkey("WIFI_STA_DEF");
    esp_netif_dhcpc_start(netif); 

    ESP_LOGI(TAG, "Connecting to %s...", ssid.c_str());

    // Block here until connected bit is set by event handler
    EventBits_t bits = xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);

    if (!(bits & CONNECTED_BIT)) 
    {
        ESP_LOGE(TAG, "Failed to get IP address - DHCP timeout");
        esp_restart(); 
    }

    ESP_LOGI(TAG, "WiFi connected");
}