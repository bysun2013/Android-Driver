/*
 * rw_semaphore.c
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

#define DEVICE_NAME "rw_semaphore"


static char *data = "read\n";
static struct rw_semaphore rw_sema;


static ssize_t rw_sema_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);
	struct timeval tv;
	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}

	do_gettimeofday(&tv);
	printk("read: start sec: %ld\n", tv.tv_sec);

	down_read(&rw_sema);

	do_gettimeofday(&tv);
	printk("read: end sec: %ld\n", tv.tv_sec);
	mdelay(5000);

	up_read(&rw_sema);

	return 0;
}

static ssize_t rw_sema_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct timeval tv;

	do_gettimeofday(&tv);
	printk("write: start sec: %ld\n", tv.tv_sec);

	down_write(&rw_sema);

	do_gettimeofday(&tv);
	printk("write: end sec: %ld\n", tv.tv_sec);

	up_write(&rw_sema);

	return count;
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = rw_sema_write,
		.read = rw_sema_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init rw_sema_init(void)
{
	int ret= misc_register(&misc);
	init_rwsem(&rw_sema);

	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit rw_sema_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(rw_sema_init);
module_exit(rw_sema_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
