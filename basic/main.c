#include <stdint.h>
#include "uart.h"
#include "riscv.h"

void kernelvec();

int main(){
	uart_init();

    w_stvec((uint64_t)kernelvec);

    puts("Hello RISCV\n");

    puts(">> Done\n");
	return 0;
}
