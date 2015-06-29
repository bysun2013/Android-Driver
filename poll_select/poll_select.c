/*
 * poll_select.c
 *
 *  Created on: Oct 9, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/poll.h>

#define DEVICE_NAME "poll_select"
#define MAX_BUFFER_SIZE 20

static char buffer[MAX_BUFFER_SIZE];
static int buf_count=0;
static wait_queue_head_t my_queue;
struct semaphore sem;



static ssize_t demo_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result=0;

	if(buf_count>0){
		if(down_interruptible(&sem))
			return -ERESTARTSYS;
//		printk("read begin: buf_count= %d\n", buf_count);
		if(copy_to_user(buf, buffer, buf_count))
			return -EINVAL;

		result= count;
		buf_count = 0;
		wake_up_interruptible(&my_queue);

		up(&sem);
//		printk("read end: buf_count= %d\n", buf_count);
		return result;
	}else
		return 0;
}

static ssize_t demo_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	ssize_t result=0;
//	printk("write begin: buf_count= %d\n", buf_count);
	if(down_interruptible(&sem))
		return -ERESTARTSYS;

	wait_event_interruptible(my_queue, buf_count==0);

	if(copy_from_user(buffer, buf, count))
		return -EINVAL;

	result=count;
	buf_count=result;

	up(&sem);
//	printk("write end: buf_count= %d\n", buf_count);
	return result;
}

static unsigned int demo_poll(struct file* filp, struct poll_table_struct *wait){

	unsigned int mask=0;

	if(down_interruptible(&sem))
		return -ERESTARTSYS;

	poll_wait(filp, &my_queue, wait);
	if(buf_count >0)
		mask |= POLLIN|POLLRDNORM;

	if(buf_count == 0)
		mask |= POLLOUT|POLLWRNORM;

	up(&sem);
	return mask;
}
static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = demo_write,
		.read = demo_read,
		.poll = demo_poll
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init demo_init(void)
{
	int ret= misc_register(&misc);

	init_waitqueue_head(&my_queue);
	sema_init(&sem, 1);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit demo_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(demo_init);
module_exit(demo_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");

