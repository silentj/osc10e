/**
 * jiffies.c
 *
 * Chapter 2 assignment - creates /proc/jiffies
 */

#include <asm/param.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define BUFFER_SIZE 128

/**
 * Function prototype for the /proc filesystem read - parameterized with a supplier function
 */
static ssize_t proc_read(u64 (* supplier)(void), struct file *file, char *buf, size_t count, loff_t *pos);

/**
 * Supplier functions for the values read by the proc filesystem
 */
static u64 jiffies_supplier(void) {
        return get_jiffies_64();
}

static u64 init_jiffies;

static u64 seconds_since_init_supplier(void) {
        return (get_jiffies_64() - init_jiffies) / HZ;
}

/**
 * The actual functions we'll put in the proc ops structs
 */
static ssize_t proc_read_jiffies(struct file *file, char *buf, size_t count, loff_t *pos) {
        return proc_read(jiffies_supplier, file, buf, count, pos);
}

static ssize_t proc_read_seconds(struct file *file, char *buf, size_t count, loff_t *pos) {
        return proc_read(seconds_since_init_supplier, file, buf, count, pos);
}

static struct file_operations proc_ops_jiffies = {
        .owner = THIS_MODULE,
        .read = proc_read_jiffies,
};

static struct file_operations proc_ops_seconds = {
        .owner = THIS_MODULE,
        .read = proc_read_seconds,
};

/* This function is called when the module is loaded. */
static int proc_init(void) {

        init_jiffies = get_jiffies_64();

        // create the /proc entries
        proc_create("jiffies", 0, NULL, &proc_ops_jiffies);
        proc_create("seconds", 0, NULL, &proc_ops_seconds);

        printk(KERN_INFO "/proc entries created\n");

	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) {

        // remove the /proc entries
        remove_proc_entry("jiffies", NULL);
        remove_proc_entry("seconds", NULL);

        printk(KERN_INFO "/proc entries removed\n");
}

/**
 * This function is called each time the /proc/jiffies is read.
 * 
 * This function is called repeatedly until it returns 0, so
 * there must be logic that ensures it ultimately returns 0
 * once it has collected the data that is to go into the 
 * corresponding /proc file.
 *
 * params:
 *
 * file:
 * buf: buffer in user space
 * count:
 * pos:
 */
static ssize_t proc_read(u64(* supplier)(void), struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "%llu", supplier());

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}


/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Proc jiffies/seconds Module");
MODULE_AUTHOR("SGG");
