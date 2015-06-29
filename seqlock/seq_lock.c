/*
 * seq_lock.c
 *
 *  Created on: Oct 6, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/atomic.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#define DEVICE_NAME "seq_lock"

static DEFINE_SEQLOCK(seq_lock);

static ssize_t seq_lock_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	unsigned seq;

	do{
		seq=read_seqbegin(&seq_lock);
		mdelay(10000);
	}while(read_seqretry(&seq_lock, seq));

	return 0;
}

static ssize_t seq_lock_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct timeval tv;

	do_gettimeofday(&tv);
	printk("write: start sec: %ld\n", tv.tv_sec);

	write_seqlock(&seq_lock);

	do_gettimeofday(&tv);
	printk("write: end sec: %ld\n", tv.tv_sec);

	write_sequnlock(&seq_lock);

	return count;
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = seq_lock_write,
		.read = seq_lock_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init seq_locks_init(void)
{
	int ret= misc_register(&misc);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit seq_locks_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(seq_locks_init);
module_exit(seq_locks_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");

