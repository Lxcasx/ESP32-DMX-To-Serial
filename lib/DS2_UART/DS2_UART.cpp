#include <hal/uart_types.h>
#include <driver/uart.h>
#include <Arduino.h>
#include "./DS2_UART.h"

/**
 * @brief Initialize the UART with the specified baud rate.
 * @param baud_rate The baud rate for the UART communication.
 */
void d2s_uart_init(int baud_rate)
{
    d2s_uart_init_custom(baud_rate, GPIO_NUM_9, GPIO_NUM_10);
}

/**
 * @brief Initialize the UART with custom TX and RX pins.
 * @param baud_rate The baud rate for the UART communication.
 * @param txd_pin The GPIO pin number for the TXD pin.
 * @param rxd_pin The GPIO pin number for the RXD pin.
 */
void d2s_uart_init_custom(int baud_rate, int txd_pin, int rxd_pin)
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

/**
 * @brief Write data to the UART.
 */
void d2s_uart_write(const char *data)
{
    uart_write_bytes(UART_NUM, data, strlen(data));
}