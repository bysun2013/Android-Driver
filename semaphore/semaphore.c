/*
 * semaphore.c
 *
 *  Created on: Oct 6, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/atomic.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#define DEVICE_NAME "semaphore"


static char *data ="read\n";

static struct semaphore sem;

static ssize_t sema_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);
	struct timeval tv;

	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}

	do_gettimeofday(&tv);
	printk("read: start sec: %ld\n", tv.tv_sec);

	down(&sem);
	mdelay(5000);
	up(&sem);

	do_gettimeofday(&tv);
	printk("read: end sec: %ld\n", tv.tv_sec);

	return 0;
}

static ssize_t sema_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct timeval tv;

	do_gettimeofday(&tv);
	printk("write: start sec: %ld\n", tv.tv_sec);

	down(&sem);

	up(&sem);

	do_gettimeofday(&tv);
	printk("write: end sec: %ld\n", tv.tv_sec);
	return count;

}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = sema_write,
		.read = sema_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init semaphore_init(void)
{
	int ret= misc_register(&misc);
	sema_init(&sem, 1);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit semaphore_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(semaphore_init);
module_exit(semaphore_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
