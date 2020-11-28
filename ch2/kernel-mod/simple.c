/**
 * simple.c
 *
 * A simple kernel module. 
 * 
 * To compile, run makefile by entering "make"
 *
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <asm/param.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>

u64 init_jiffies;

/* This function is called when the module is loaded. */
static int simple_init(void)
{
       init_jiffies = get_jiffies_64();

       printk(KERN_INFO "Loading Module\n");
       printk(KERN_INFO "Hertz:   %i\n", HZ);
       printk(KERN_INFO "Jiffies: %llu\n", init_jiffies);

       return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {
       u64 elapsed_jiffies = get_jiffies_64() - init_jiffies;
       u64 elapsed_seconds = elapsed_jiffies / HZ;

	printk(KERN_INFO "Removing Module\n");
       printk(KERN_INFO "Jiffies: %llu\n", get_jiffies_64());
       printk(KERN_INFO "Elapsed jiffies: %llu\n", elapsed_jiffies);
       printk(KERN_INFO "Elapsed seconds: %llu\n", elapsed_seconds);
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

