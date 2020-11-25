
QEMU=qemu-system-riscv64 -machine virt -bios none -m 128M -nographic

CROSS_COMPILE=riscv64-unknown-elf-
LD=${CROSS_COMPILE}ld
CC=${CROSS_COMPILE}gcc
OBJDUMP=${CROSS_COMPILE}objdump
NM=${CROSS_COMPILE}nm
GDB=${CROSS_COMPILE}gdb

PROG=basic

all: ${PROG}

CFLAGS=-O0 -g -Wall

LDFLAGS=--gc-sections -nostartfiles -nostdlib -nodefaultlibs

%.o:%.c
	${CC} -c ${CFLAGS} -o $@ $<

%.o:%.S
	${CC} -c ${CFLAGS} -o $@ $<

OBJS=main.o startup.o uart.o #ns16550a.o

${PROG}: ${OBJS}
	${LD} ${LDFLAGS} -Triscv64-virt.ld -o $@ $^

run:${PROG}
	${QEMU} -kernel ${PROG}

gdb_server:${PROG}
	${QEMU} -gdb tcp::1234 -S -kernel ${PROG}


gdb_client:${PROG}
	${GDB} ${PROG} -ex "target remote :1234" -ex "b main"	

section:${PROG}
	${OBJDUMP} -hww ${PROG}

symbols:${PROG}
	${OBJDUMP} -t ${PROG}

asm:${PROG}
	${OBJDUMP} -D ${PROG} > ${PROG}.s

nm:${PROG}
	${NM} $<

dts:
	${QEMU} -machine dumpdtb=riscv64-virt.dtb
	dtc -I dtb -O dts -o riscv64-virt.dts riscv64-virt.dtb

lds:
	$(LD) --verbose > riscv64-virt-verbose.ld

clean:
	-rm ${PROG} *.dtb *.dts riscv64-virt-verbose.ld *.o *.s -rf
