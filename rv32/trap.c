#include <stdint.h>
#include "riscv.h"
#include "uart.h"
#include "plic.h"
#include "sysdefs.h"
#include "printf.h"

void uartintr(void) {
    while(1) {
        int c = uart_getc();
        if(c == -1) {
            break;
        }
        uart_putc('>');
        uart_putc(c);
        uart_putc('\n');
    }
}

void virtio_disk_intr(int i) {
    puts("virtio_disk_intr\n");
}


volatile uint64_t ticks;


void clockintr() {
    ticks++;
    printf("Tick:%d\n", ticks);
}


void kerneltrap() {
    uint64_t sepc = r_sepc();
    uint64_t sstatus = r_sstatus();
    uint64_t scause = r_scause();

    if((sstatus & SSTATUS_SPP) == 0) {
        panic("kerneltrap: not from supervisor mode");
    }
    if(intr_get() != 0) {
        panic("kerneltrap: interrupts enabled");
    }

    if((scause & 0x8000000000000000L) && (scause & 0xff) == 9) {
        // this is a supervisor external interrupt, via PLIC.

        // irq indicates which device interrupted.
        int irq = plic_claim();

        if(irq == UART0_IRQ) {
            uartintr();
        } else
            if(irq == VIRTIO0_IRQ || irq == VIRTIO1_IRQ ) {
                virtio_disk_intr(irq - VIRTIO0_IRQ);
            }
        plic_complete(irq);
    } else {
        if(scause == 0x8000000000000001L) {
            // software interrupt from a machine-mode timer interrupt,
            // forwarded by timervec in kernelvec.S.
            if(cpuid() == 0) {
                clockintr();
            }
            // acknowledge the software interrupt by clearing
            // the SSIP bit in sip.
            w_sip(r_sip() & ~2);
        }
    }
    // the yield() may have caused some traps to occur,
    // so restore trap registers for use by kernelvec.S's sepc instruction.
    w_sepc(sepc);
    w_sstatus(sstatus);
}
