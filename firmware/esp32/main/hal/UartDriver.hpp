#pragma once

#include <cstdint>

#include "driver/gpio.h"

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
    UartDriver(int b) : baudRate(b) {};
    void init();
    void startRxTask();

private: 
    int baudRate;
    static constexpr const char* RX_TASK_TAG = "RX_TASK"; 
    static constexpr int RX_BUF_SIZE = 128; 
    static void rxTask(void *arg); 
};