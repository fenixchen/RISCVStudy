#ifndef _UART_H_
#define _UART_H_

void uart_init(void);

void uart_putc(int c);

void uart_puts(const char* s);

#define puts uart_puts

#define panic uart_puts

#endif
