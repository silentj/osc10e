Simple kernel module
====================

Making (in Linux VM)

    make

Loading the module

    sudo insmod simple.ko

Showing the loaded modules

    lsmod

Showing the kernel log

    dmesg

Clearing the kernel log

    sudo dmesg -c

Unloading the module

    sudo rmmod simple
