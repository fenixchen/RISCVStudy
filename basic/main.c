#include <stdint.h>
#include "uart.h"
#include "riscv.h"

void kernelvec();

int main(){
	int a = 10;
	int b = 20;
	int c = 0;

	uart_init();

    w_stvec((uint64_t)kernelvec);

    uart_puts("Hello RISCV\n");

	while (1){
		c = a + b;
	}
	while (c--){
	}
	return 0;
}
