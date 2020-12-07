# riscv-tools

sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev


# download opcodes
git clone https://github.com/riscv/riscv-opcodes

sudo apt-get install python3-pip
sudo pip3 install future


vi opcodes-rv32i
// add line

dot     rd rs1 rs2 31..25=1  14..12=0 6..2=0x1A 1..0=3

./parse_opcodes -c opcodes-rv32i  > dot.h

# download toolchain source
git clone https://gitee.com/mirrors/riscv-gnu-toolchain.git

git clone https://github.com/riscv/riscv-gnu-toolchain.git

cd riscv-gnu-toolchain
git submodule update --init riscv-binutils
git submodule update --init riscv-gcc
git submodule update --init riscv-glibc
git submodule update --init riscv-dejagnu
git submodule update --init riscv-newlib
git submodule update --init riscv-gdb

