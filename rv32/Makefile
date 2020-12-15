
QEMU=qemu-system-riscv32 -machine virt -bios none -m 128M -nographic

CROSS_COMPILE=riscv32-unknown-elf-
LD=${CROSS_COMPILE}gcc
CC=${CROSS_COMPILE}gcc
OBJDUMP=${CROSS_COMPILE}objdump
NM=${CROSS_COMPILE}nm
GDB=${CROSS_COMPILE}gdb

PROG=rv32_test

all: ${PROG}

CFLAGS=-O0 -g -Wall -mcmodel=medany

LDFLAGS=-Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs

%.o:%.c
	${CC} -c ${CFLAGS} -o $@ $<

%.o:%.S
	${CC} -c ${CFLAGS} -o $@ $<


C_SRCS=$(wildcard *.c)

ASM_SRCS=$(wildcard *.S)

OBJS=$(patsubst %.c,%.o,${C_SRCS})

OBJS+=$(patsubst %.S,%.o,${ASM_SRCS})

${PROG}: ${OBJS}
	${LD} ${LDFLAGS} -Triscv32-virt.ld -o $@ $^ -lc -lgcc

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
	${QEMU} -machine dumpdtb=riscv32-virt.dtb
	dtc -I dtb -O dts -o riscv32-virt.dts riscv32-virt.dtb

lds:
	$(CROSS_COMPILE)ld --verbose > riscv32-virt-verbose.ld

clean:
	-rm ${PROG} *.dtb *.dts riscv32-virt-verbose.ld *.o *.s -rf

format:
	astyle --style=google "*.h" -R -n -p -e -j
	astyle --style=google "*.c" -R -n -p -e -j
