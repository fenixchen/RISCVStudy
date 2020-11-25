#include "uart.h"


int main(){
	int a = 10;
	int b = 20;
	int c = 0;

	uart_init();
	uart_putc('A');
	uart_putc('B');
	uart_putc('C');
	uart_putc('D');
	uart_putc('\n');

	while (1){
		c = a + b;
	}
	while (c--){
	}
	return 0;
}
