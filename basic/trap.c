#include <stdint.h>
#include "riscv.h"
#include "uart.h"


void kerneltrap() {
    int which_dev = 0;
    uint64_t sepc = r_sepc();
    uint64_t sstatus = r_sstatus();
    uint64_t scause = r_scause();
    
    if((sstatus & SSTATUS_SPP) == 0) {
        panic("kerneltrap: not from supervisor mode");
    }
    if(intr_get() != 0) {
        panic("kerneltrap: interrupts enabled");
    }

#if 0
    if((which_dev = devintr()) == 0) {
        printf("scause %p\n", scause);
        printf("sepc=%p stval=%p\n", r_sepc(), r_stval());
        panic("kerneltrap");
    }

#endif

    // the yield() may have caused some traps to occur,
    // so restore trap registers for use by kernelvec.S's sepc instruction.
    w_sepc(sepc);
    w_sstatus(sstatus);
}
