#pragma once

#include <cstdint>

#include "driver/gpio.h"
#include "UdpSender.hpp"

#define RXD_PIN (GPIO_NUM_16)
#define TXD_PIN (GPIO_NUM_17)

/** 
 * @brief Configures GPIO port for UART
 */
class UartDriver {
public: 
    /**
     * @brief Constructs UART configuration
     * @param   baudRate   Baud rate for UART communicatikon 
     */
    UartDriver(int b, UdpSender* s) : baudRate(b),  sender(s) {};
    void init();
    void startRxTask();
    void sendCommand(std::string cmd); // In public for testing only

private: 
    int baudRate;
    UdpSender* sender; 
    static void receiveRxData(void *arg); 
};