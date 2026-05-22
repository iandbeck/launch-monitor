#include "UartDriver.hpp"

#include "driver/uart.h"
#include "esp_err.h"

#include <string>


void UartDriver::init() 
{
    uart_config_t uart_config = {};
    uart_config.baud_rate      = baudRate;
    uart_config.data_bits      = UART_DATA_8_BITS; 
    uart_config.parity         = UART_PARITY_DISABLE; 
    uart_config.stop_bits      = UART_STOP_BITS_1; 
    uart_config.flow_ctrl      = UART_HW_FLOWCTRL_DISABLE; 
    uart_config.source_clk     = UART_SCLK_DEFAULT;
    uart_config.rx_flow_ctrl_thresh = 0;

    uart_param_config(UART_NUM_2, &uart_config); 
    uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 2, 0, 0, NULL, 0); 
}

void UartDriver::startRxTask() 
{
    xTaskCreate(
        rxTask, 
        RX_TASK_TAG, 
        4096, 
        this, 
        5, 
        nullptr
    );
}

void UartDriver::rxTask(void *arg)
{
    auto *self = static_cast<UartDriver *>(arg); 
    esp_log_level_set(self->RX_TASK_TAG, ESP_LOG_INFO); 
    uint8_t data[self->RX_BUF_SIZE + 1]; // + 1 for safe null termination
    
    while(1) 
    {
        int rxBytes = uart_read_bytes(UART_NUM_2, data, self->RX_BUF_SIZE, portMAX_DELAY); 
        if (rxBytes > 0) 
        {
            data[rxBytes] = '\0'; // null terminate buffer
            ESP_LOGI(self->RX_TASK_TAG, "Read %d bytes '%s'", rxBytes, data);
        }
    }
}