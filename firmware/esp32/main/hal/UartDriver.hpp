#pragma once

#include <cstdint>

#include "driver/gpio.h"
#include "UdpSender.hpp"

#define RXD_PIN (GPIO_NUM_16)
#define TXD_PIN (GPIO_NUM_17)
#define HOST_INT_PIN (GPIO_NUM_4)

static constexpr const char* RX_TASK_TAG = "UartDriver [RX]"; 
static constexpr const char* TX_TASK_TAG = "UartDriver [TX]"; 
static constexpr const char* TRIGGER_TASK_TAG = "UartDriver [Trigger]";
static constexpr int RX_BUF_SIZE = 2048; 

/** 
 * @brief Configures GPIO port for UART
 */
class UartDriver {
public: 
    /**
     * @brief Constructs UART configuration
     * @param   baudRate   Baud rate for UART communicatikon 
     */
    UartDriver(int b, UdpSender* s);
    void startRxTask();

    
    void sendCommand(std::string cmd); // In public for testing only
    void triggerPulse(); // Also in public only for testing

private: 
    int baudRate;
    UdpSender* sender; 
    static void receiveRxData(void *arg); 
    void initUart();
    void initTriggerPin();
};