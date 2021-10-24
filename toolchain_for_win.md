https://shadowcode.io/compile-risc-v-gnu-toolchain-for-windows/

sudo apt-get install -y gcc g++ gperf bison flex texinfo help2man make libncurses5-dev  python3-dev autoconf automake libtool libtool-bin gawk wget bzip2 xz-utils unzip patch libstdc++6 rsync git mingw-w64


git clone --recursive https://github.com/stephanosio/zephyr-crosstool-ng ct-ng

cd ct-ng

Inside the /ct-ng/samples directory copy the riscv32-unknown-elf folder.

Rename the folder to “x86_64-w64-mingw32,riscv32-unknown-elf”

Enter the folder you just created and open the “crosstool.config” file, add the following two lines of text to the bottom of the file.

CT_CANADIAN=y
CT_HOST="x86_64-w64-mingw32"

./bootstrap

./configure --prefix=/home/ryno/Desktop/zt-ng

make

make install

cd ../zt-ng/bin

./ct-ng x86_64-w64-mingw32,riscv32-unknown-elf

./ct-ng menuconfig

Enter the “Paths and misc options” submenu, scroll down and select “Stop after extracting tarballs”. 
We do this initially because we need to edit some files in the GCC package that ct-ng downloads. 
After we have edited those files we will come back here and disable this setting which will allow ct-ng to progress past this point and finish the build process. 
ct-ng will not re-download or extract the tarballs a second time.


Go back to the main menu and enter the “Target options” submenu. Select “Build a multilib toolchain”.

Go back to the main menu and enter the “C-Library” submenu. Here select “Newlib” as the C library. Several more options will be enabled. 
Scroll down and select “Enable newlib nano variant” as well.

[Optional] Under the options for “Enable Newlib nano variant” deselect the “Optimize newlib for size” option. 
You can select this option if you wish, however you will need to manually strip the binaries afterwards because that does not happen as part of the size optimizations so you end up with binaries that are actually larger.

[Optional] Go back to the main menu and enter the “C Compiler” submenu, scroll to the bottom and select “C++”.

./ct-ng build


