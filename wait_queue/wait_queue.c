/*
 * wait_queue.c
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
#include <linux/wait.h>
#include <linux/sched.h>

#define DEVICE_NAME "wq"
#define MAX_BUFFER_SIZE 20

static char buffer[MAX_BUFFER_SIZE];
static int buf_count=0;
static wait_queue_head_t my_queue;



static ssize_t wq_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result=0;

	if(buf_count>0){
		printk("read begin: buf_count= %d\n", buf_count);
		if(copy_to_user(buf, buffer, buf_count))
			return -EINVAL;

		result= count;
		buf_count = 0;
		wake_up_interruptible(&my_queue);

		printk("read end: buf_count= %d\n", buf_count);
		return result;
	}else
		return 0;
}

static ssize_t wq_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result=0;
	printk("write begin: buf_count= %d\n", buf_count);

	wait_event_interruptible(my_queue, buf_count==0);

	if(copy_from_user(buffer, buf, count))
		return -EINVAL;

	result=count;
	buf_count=result;
	printk("write end: buf_count= %d\n", buf_count);
	return result;
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = wq_write,
		.read = wq_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init wq_init(void)
{
	int ret= misc_register(&misc);
	init_waitqueue_head(&my_queue);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit wq_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(wq_init);
module_exit(wq_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");

