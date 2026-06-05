#include "UdpSender.hpp"

#include <stdexcept> 
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "esp_log.h"
#include "esp_system.h"

static const char* TAG = "UdpSender";

UdpSender::UdpSender(const std::string& host, int port) 
    : host_(host), port_(port), sock_(-1) 
{ 
    sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock_ < 0)
    {
        ESP_LOGE(TAG, "Failed to create Udp socket");
        // Restart the device
        esp_restart();
    }

    ESP_LOGI(TAG, "Udp sender ready -> %s:%d", host_.c_str(), port_);
}

UdpSender::~UdpSender() 
{
    if (sock_ >= 0) 
    {
        close(sock_); 
    }
}

void UdpSender::send(const uint8_t* data, size_t length) {
    sockaddr_in dest{}; 
    dest.sin_family = AF_INET; 
    dest.sin_port = htons(port_); 
    inet_pton(AF_INET, host_.c_str(), &dest.sin_addr);

    int result = sendto(sock_, 
                        data,
                        length, 
                        0, 
                        (sockaddr*)&dest, 
                        sizeof(dest));

    if (result < 0) 
    {
        ESP_LOGE(TAG, "Failed to send packet");
    }
}