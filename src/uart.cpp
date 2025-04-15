#include <hal/uart_types.h>
#include <driver/uart.h>
#include <Arduino.h>
#include "./uart.h"

#define UART_NUM UART_NUM_1

void uart_init(int baud_rate)
{
    uart_init_custom(baud_rate, GPIO_NUM_9, GPIO_NUM_10);
}

void uart_init_custom(int baud_rate, int txd_pin, int rxd_pin)
{
    uart_config_t uart_config = {
        .baud_rate = 230400,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, txd_pin, rxd_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);
}

void uart_write(const char *data)
{
    uart_write_bytes(UART_NUM, data, strlen(data));
}