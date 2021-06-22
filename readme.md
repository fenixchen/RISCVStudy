# riscv-tools

```
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev libusb-1.0-0-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev device-tree-compiler pkg-config libexpat-dev
```


# download opcodes
```shell
git clone https://github.com/riscv/riscv-opcodes

sudo apt-get install python3-pip
sudo pip3 install future


vi opcodes-rv32i
// add line

dot     rd rs1 rs2 31..25=1  14..12=0 6..2=0x1A 1..0=3

./parse_opcodes -c opcodes-rv32i  > dot.h 
```

# download toolchain source
```shell
git clone https://github.com/riscv/riscv-gnu-toolchain.git

git clone https://gitee.com/mirrors/riscv-gnu-toolchain.git

cd riscv-gnu-toolchain
git submodule update --init riscv-binutils
git submodule update --init riscv-gcc
git submodule update --init riscv-glibc
git submodule update --init riscv-dejagnu
git submodule update --init riscv-newlib
git submodule update --init riscv-gdb
```




# build rv32 toolchain

```shell
./configure --prefix=/opt/rv32 --with-arch=rv32imac --with-abi=ilp32

sudo make -j15
```




## build with multilib
./configure --prefix=/opt/riscv --enable-multilib

# Change binutils

vi riscv-gnu-toolchain/riscv-binutils/include/opcode/riscv-opc.h

// add two lines
```c


 #define MASK_OR  0xfe00707f
 #define MATCH_AND 0x7033
 #define MASK_AND  0xfe00707f
+
+#define MATCH_HAHA 0x200006b
+#define MASK_HAHA  0xfe00707f
+
 #define MATCH_ADDIW 0x1b
 #define MASK_ADDIW  0x707f
 #define MATCH_SLLIW 0x101b
@@ -892,6 +896,7 @@ DECLARE_INSN(srl, MATCH_SRL, MASK_SRL)
 DECLARE_INSN(sra, MATCH_SRA, MASK_SRA)
 DECLARE_INSN(or, MATCH_OR, MASK_OR)
 DECLARE_INSN(and, MATCH_AND, MASK_AND)
+DECLARE_INSN(haha, MATCH_HAHA, MASK_HAHA)
 DECLARE_INSN(addiw, MATCH_ADDIW, MASK_ADDIW)
 DECLARE_INSN(slliw, MATCH_SLLIW, MASK_SLLIW)
 DECLARE_INSN(srliw, MATCH_SRLIW, MASK_SRLIW)


```
vi riscv-gnu-toolchain/riscv-binutils/opcodes/riscv-opc.c

```c

 {"sfence.vma", 0, INSN_CLASS_I,   "s,t",  MATCH_SFENCE_VMA, MASK_SFENCE_VMA, match_opcode, 0 },
 {"wfi",        0, INSN_CLASS_I,   "",     MATCH_WFI, MASK_WFI, match_opcode, 0 },
 
+{"haha",       0, INSN_CLASS_I,   "d,s,t",  MATCH_HAHA, MASK_HAHA, match_opcode, 0 },
+
 /* Terminate the list.  */
 {0, 0, INSN_CLASS_NONE, 0, 0, 0, 0, 0}
 };

```


# build


./configure --prefix=/opt/rv32_with_haha --with-arch=rv32imac --with-abi=ilp32

sudo make -j15




# test

```c
vi haha_test.c

void haha_test(int res){
    asm volatile ("haha %[output], a0, a1\t\n" \
                  :[output]"=r"(res));
}

void main(void){
    int res;
    haha_test(res);
}



/opt/rv32_with_haha/bin/riscv32-unknown-elf-gcc -o haha haha_test.c

/opt/rv32_with_haha/bin/riscv32-unknown-elf-objdump -d haha
```

