/*************************************************************
* Project:   /dev/e                                          *
* File:      e_driver.c                                      *
* Name:      Sabrina Aravena                                 *
**************************************************************/

#include <linux/fs.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include "e.h"

/* Figures out buffer and max size and passes in the e from e.h */
static ssize_t e_driver_read(struct file * file, char * buf, size_t count, loff_t *ppos) {
	/* calculates sum */
	int sum = count + (int) *ppos;
	char buff[sum];
	/* function implementation in "e.h" */
	e(buff, sum);

	/* checks that the user has permission to write to the buffer */
	if (copy_to_user(buf, &buff[*ppos], count))
		return -EINVAL;
	/* how much data was written */
	*ppos = count;
	return count;
} /* end ssize_t e_driver_read(struct, char*, size_t, loff_t) */

/* Read op needed */
static const struct file_operations e_driver_fops = {
	.owner		= THIS_MODULE,
	.read		= e_driver_read,
};

static struct miscdevice e_driver = {
	/* kernel chooses a random num for MINOR */
	MISC_DYNAMIC_MINOR,
	/* Name ourselves /dev/e */
	"e_driver",
	/* determines what functions to call */
	&e_driver_fops
};

static int __init
e_driver_init(void) {
	int ret;

	/*
	 * Creates the device in the /sys/class/misc directory. */
	ret = misc_register(&e_driver);
	if (ret)
		printk(KERN_ERR
		       "Unable to register e_driver misc device\n");

	return ret;
} /* end e_driver_inti() */

module_init(e_driver_init);

static void __exit
e_driver_exit(void) {
	misc_deregister(&e_driver);
} /* end e_driver_exit() */

/* Exit module */
module_exit(e_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sabrina Aravena <saa154>");
MODULE_DESCRIPTION("e_driver minimal module");
MODULE_VERSION("dev");
