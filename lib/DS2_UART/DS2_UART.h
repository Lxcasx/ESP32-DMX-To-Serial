#ifndef UART_H
#define UART_H

#include <hal/uart_types.h>
#include <driver/uart.h>

#define UART_NUM UART_NUM_1

void d2s_uart_init(int baud_rate);
void d2s_uart_init_custom(int baud_rate, int txd_pin, int rxd_pin);
void d2s_uart_write(const char *data);

#endif // UART_H