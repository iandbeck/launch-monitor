#include "UartDriver.hpp"
#include "driver/uart.h"
#include "esp_err.h"

#include <iostream>
#include <string>

UartDriver::UartDriver(int b, UdpSender *s) : baudRate(b), sender(s)
{
    initUart();
    initTriggerPin();
}

void UartDriver::initUart()
{
    // Configure UART port 2 (GPIO 16/17)
    uart_config_t uart_config = {};
    uart_config.baud_rate = baudRate;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
    uart_config.source_clk = UART_SCLK_DEFAULT;
    uart_config.rx_flow_ctrl_thresh = 0;

    uart_param_config(UART_NUM_2, &uart_config);
    uart_set_pin(UART_NUM_2, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE,
                 UART_PIN_NO_CHANGE);
    // Ensure ring buffer is large enough to ensure
    // no bytes are dropped between reads (RX_BUF_SIZE * 4)
    uart_driver_install(UART_NUM_2, RX_BUF_SIZE * 32, 0, 0, NULL, 0);
}

void UartDriver::initTriggerPin()
{
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = (1Ull << HOST_INT_PIN);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    // Ensure parts starts low
    gpio_set_level(HOST_INT_PIN, 0);
}

void UartDriver::triggerPulse()
{
    ESP_LOGI(TRIGGER_TASK_TAG, "Sending 10 ms trigger pulse");
    // 10ms 3.3V pulse
    gpio_set_level(HOST_INT_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(HOST_INT_PIN, 0);
}

void UartDriver::startRxTask()
{
    ESP_LOGI(RX_TASK_TAG, "Starting data receive from doppler module");
    xTaskCreate(receiveRxData, RX_TASK_TAG, 32768, this, 5, nullptr);
}

void UartDriver::receiveRxData(void *arg)
{
    auto *self = static_cast<UartDriver *>(arg);
    uint8_t data[RX_BUF_SIZE];
    size_t dataIndex = 0;
    size_t bytesAvailable = 0;
    size_t rxBytes = 0;
    // char c;

    while (1)
    {
        // Check # bytes in rx buffer
        uart_get_buffered_data_len(UART_NUM_2, &bytesAvailable);

        if (bytesAvailable > 0)
        {
            rxBytes = uart_read_bytes(UART_NUM_2, data, bytesAvailable, portMAX_DELAY);
            if (rxBytes > 0)
            {
                // Append null character to end of rx data (overwrite \n)
                data[rxBytes] = '\0';
                ESP_LOGD(RX_TASK_TAG, "%s", data);
            }
        }
        else
        {
            // No data available, yield and check again shortly
            vTaskDelay(pdMS_TO_TICKS(10));
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