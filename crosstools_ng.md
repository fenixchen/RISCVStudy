# download and build

git clone https://github.com/crosstool-ng/crosstool-ng.git


./configure --prefix=/home/train/ct-ng


make && make install


export PATH=$PATH:~/ct-ng/bin

# build toolchain for linux

add python support

sudo apt install python-dev libpython-dev


ls /home/train/ct-ng/share/crosstool-ng/samples/riscv32-unknown-elf

./ct-ng riscv32-unknown-elf


## ./ct-ng menuconfig

- target
(rv32imc) Architecture level
(ilp32) Generate code for the specific ABI 

- toolchain
[*] Build Static Toolchain

- C Library
C library (none) 

- C Compiler
[*] C++

- Debug facilities

[*] gdb
Version of gdb (9.2)

-  Companion libraries
[*] newlib-nano
(-march=rv32imc -mabi=ilp32 -mcmodel=medany) Target CFLAGS for newlib

Place each function & data element in their own section



# build for windows

cd ~/ct-ng/share/crosstool-ng/samples

cp riscv32-unknown-elf/ riscv32-unknown-elf.mingw32  -rf

cd riscv32-unknown-elf.mingw32

vi crosstool.config

Add two lines

CT_CANADIAN=y

CT_HOST="x86_64-w64-mingw32"


cd build_win

ct-ng riscv32-unknown-elf.mingw32

