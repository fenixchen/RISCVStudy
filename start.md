# docs

- [doc1](https://twilco.github.io/riscv-from-scratch/2019/03/10/riscv-from-scratch-1.html)

- [doc2](https://twilco.github.io/riscv-from-scratch/2019/04/27/riscv-from-scratch-2.html)

- [doc3](https://twilco.github.io/riscv-from-scratch/2019/07/08/riscv-from-scratch-3.html)

- [doc4](https://twilco.github.io/riscv-from-scratch/2019/07/28/riscv-from-scratch-4.html)

- [DeviceTree](https://elinux.org/Device_Tree_Usage)


# toolchain

## get toolchain source
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain

## build with multilib
./configure --prefix=/opt/riscv --enable-multilib


# Simple test

[freedom-e-sdk](https://github.com/sifive/freedom-e-sdk)

git clone --recursive https://github.com/sifive/freedom-e-sdk.git

cd freedom-e-sdk

make PROGRAM=hello TARGET=sifive-hifive1 CONFIGURATION=debug software

qemu-system-riscv32 -nographic -machine sifive_e -kernel software/hello/debug/hello.elf

>> Hello, World!


# Build from scratch


## check build config

riscv64-unknown-elf-gcc add.c -O0 -g -v

crt0.o, crtbegin.o, -lgcc, --start-group

## Target triplet

[Information](https://wiki.osdev.org/Target_Triplet)

- Target triplet: riscv64-unknown-elf, machine-vendor-operatingsystem
- Target ISA: rv64imafdc
- Target ABI, lp64d

## check device tree

[device tree spec](https://buildmedia.readthedocs.org/media/pdf/devicetree-specification/latest/devicetree-specification.pdf)

qemu-system-riscv64 -machine virt -machine dumpdtb=riscv64-virt.dtb

dtc -I dtb -O dts -o riscv64-virt.dts riscv64-virt.dtb

```
        #address-cells = <0x02>;
        #size-cells = <0x02>;
        compatible = "riscv-virtio";
        model = "riscv-virtio,qemu";

        memory@80000000 {
                device_type = "memory";
                reg = <0x00 0x80000000 0x00 0x8000000>;
        };

```

Memory range(0x00 + 0x80000000, len: 0x00 + 0x8000000), 128M


## what is CRTx

```

## Link scripts

// export default one

riscv64-unknown-elf-ld --verbose > riscv64-virt.ld

```shell

OUTPUT_ARCH(riscv)
/* Add Begin */
MEMORY
{
   /* qemu-system-risc64 virt machine */
   RAM (rwx)  : ORIGIN = 0x80000000, LENGTH = 128M 
}
/* Add End */

SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x10000));
  . = SEGMENT_START("text-segment", 0x10000) + SIZEOF_HEADERS;
  /* >>> Our addition. <<< */
  PROVIDE(__stack_top = ORIGIN(RAM) + LENGTH(RAM));
  /* >>> End of our addition. <<< */
  .interp         : { *(.interp) }
  ...
}


```

# Own crt0.s


## [CFI reference](https://sourceware.org/binutils/docs/as/CFI-directives.html)

```c

/* section .init, a: allocatable, x: executable */
.section .init, "ax"

/* make the symbol available to ld, ENTRY(_start) */
.global _start


/* we start at symbol _start */
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
    jal zero, main

    /* end function */
    .cfi_endproc

    /* end of asm file */
    .end

```

## RISC-V register conventions

[RISC-V assembly guide](https://github.com/riscv/riscv-asm-manual/blob/master/riscv-asm.md#general-registers)







# Link

-ffeestanding

[the standard library may not exists](https://stackoverflow.com/questions/17692428/what-is-ffreestanding-option-in-gcc#17692510)





