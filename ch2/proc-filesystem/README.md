Creating entries in the /proc filesystem
========================================

Making (in Linux VM)

    make

Loading the module

    sudo insmod jiffies.ko

Viewing the jiffies since the system has started

    cat /proc/jiffies

Viewing the number of seconds since the module was loaded

    cat /proc/seconds

Showing the loaded modules

    lsmod

Unloading the module

    sudo rmmod simple

Showing the kernel log

    dmesg

Clearing the kernel log

    sudo dmesg -c
