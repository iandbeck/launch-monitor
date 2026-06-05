#include "UartDriver.hpp"

#include "driver/uart.h"
#include "esp_err.h"

#include <string>

static constexpr const char* RX_TASK_TAG = "UartDriver [RX]"; 
static constexpr const char* TX_TASK_TAG = "UartDriver [TX]"; 
static constexpr int RX_BUF_SIZE = 64; 


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
    // Ensure ring buffer is large enough to ensure 
    // no bytes are dropped between reads (RX_BUF_SIZE * 4)
    uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 4, 0, 0, NULL, 0);

    // Set UART rx timeout so that we receive data quicker
    uart_set_rx_timeout(UART_NUM_2, 10); // 10 character times of inactivity
}

void UartDriver::startRxTask() 
{
    ESP_LOGI(RX_TASK_TAG, "Starting data receive from doppler module");
    xTaskCreate(
        receiveRxData, 
        RX_TASK_TAG, 
        4096, 
        this, 
        5, 
        nullptr
    );
}

void UartDriver::receiveRxData(void *arg)
{
    auto *self = static_cast<UartDriver *>(arg); 
    uint8_t data[RX_BUF_SIZE]; 
    size_t dataIndex = 0;
    char c;
    
    while(1) 
    {
        // Continually monitor radar module speed output
        int rxBytes = uart_read_bytes(UART_NUM_2, &c, 1, portMAX_DELAY); 
        if (rxBytes > 0) 
        {
            if (c == '\n')
            {
                // Print buffer data 
                data[dataIndex] = '\0';
                ESP_LOGD(RX_TASK_TAG, "%s", data);

                // Reset buffer position
                dataIndex = 0; 
            } else
            {
                // Append data to buffer
                data[dataIndex] = c; 
                dataIndex++;
            }
        } else 
        {
            ESP_LOGE(RX_TASK_TAG, "ERROR: Received -1 from uart read"); 
        }
    }
}

// Sends string over UART to connected device
void UartDriver::sendCommand(std::string cmd)
{
    std::string uartCmd = cmd + "\r\n"; // Ensure correct line endings
    ESP_LOGI(TX_TASK_TAG, "Sending '%s' to doppler module", cmd.c_str());
    uart_write_bytes(UART_NUM_2, uartCmd.c_str(), uartCmd.size());
}