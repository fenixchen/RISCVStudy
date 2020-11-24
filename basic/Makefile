
QEMU=qemu-system-riscv64 -machine virt -bios none -m 128M -nographic

CROSS_COMPILE=riscv64-unknown-elf-
LD=${CROSS_COMPILE}ld
CC=${CROSS_COMPILE}gcc
OBJDUMP=${CROSS_COMPILE}objdump
GDB=${CROSS_COMPILE}gdb

PROG=basic

all: ${PROG}

CFLAGS=-O0 -g -Wall

LDFLAGS=--gc-sections -nostartfiles -nostdlib -nodefaultlibs

%.o:%.c
	${CC} -c ${CFLAGS} -o $@ $<

%.o:%.S
	${CC} -c ${CFLAGS} -o $@ $<

${PROG}: main.o startup.o
	${LD} ${LDFLAGS} -Triscv64-virt.ld -o $@ $^

gdb_server:${PROG}
	${QEMU} -gdb tcp::1234 -S -kernel ${PROG}


gdb_client:${PROG}
	${GDB} ${PROG} -ex "target remote :1234" -ex "b main"	

section:
	${OBJDUMP} -hww ${PROG}

symbols:
	${OBJDUMP} -t ${PROG}

asm:
	${OBJDUMP} -D ${PROG} > ${PROG}.s

dts:
	${QEMU} -machine dumpdtb=riscv64-virt.dtb
	dtc -I dtb -O dts -o riscv64-virt.dts riscv64-virt.dtb

lds:
	$(LD) --verbose > riscv64-virt-verbose.ld

clean:
	-rm ${PROG} *.dtb *.dts riscv64-virt-verbose.ld *.o *.s -rf
