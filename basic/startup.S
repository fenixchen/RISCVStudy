/* section .init, a: allocatable, x: executable */
.section .init, "ax"

/* make the symbol available to ld, ENTRY(_start) */
.global _start

_start:
    /* start function */
    .cfi_startproc

    /* ra should not be restore */
    .cfi_undefined ra

    /* save assembly options */
    .option push

    /* since we relax addressing sequences to shorter GP-relative sequences when possible,
       the initial load of GP must not be relaxed and should be emitted as something like:
       https://embarc.org/man-pages/as/RISC_002dV_002dDirectives.html*/
    .option norelax

    la gp, __global_pointer$

    /* restore assembly options */
    .option pop

    /* stack pointer */
    la sp, __stack_top

    /* set frame pointer s0 as 0 */
    add s0, sp, zero
    
    /* jump and link
       set next pc(pc + 4) to rd, then set pc = pc + offset
       free jump
    */
    jal zero, boot_main

    /* end function */
    .cfi_endproc

    .end
