/*
 * mutex.c
 *
 *  Created on: Oct 8, 2013
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

#define DEVICE_NAME "mutex"


static char *data ="read\n";

static struct mutex mtx;

static ssize_t mutex_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);
	struct timeval tv;

	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}

	do_gettimeofday(&tv);
	printk("read: start sec: %ld\n", tv.tv_sec);

	mutex_lock(&mtx);
	mdelay(5000);
	mutex_unlock(&mtx);

	do_gettimeofday(&tv);
	printk("read: end sec: %ld\n", tv.tv_sec);

	return 0;
}

static ssize_t mutex_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct timeval tv;

	do_gettimeofday(&tv);
	printk("write: start sec: %ld\n", tv.tv_sec);

	mutex_lock(&mtx);

	mutex_unlock(&mtx);

	do_gettimeofday(&tv);
	printk("write: end sec: %ld\n", tv.tv_sec);
	return count;

}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = mutex_write,
		.read = mutex_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init mutexs_init(void)
{
	int ret= misc_register(&misc);
	mutex_init(&mtx);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit mutexs_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(mutexs_init);
module_exit(mutexs_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
