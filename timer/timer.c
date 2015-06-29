/*
 * timer.c
 *
 *  Created on: Oct 12, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "timer_demo"
struct timer_dev{
	atomic_t counter;
	struct timer_list s_timer;
};

static struct timer_dev *timer_devp;

static void timer_demo_handler(unsigned long arg){
	mod_timer(&timer_devp->s_timer, jiffies+HZ);
	atomic_inc(&timer_devp->counter);

	printk("current jiffies is %ld\n", jiffies);
}

static ssize_t demo_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos){
	int counter = atomic_read(&timer_devp->counter);
	if(put_user(counter, (int *)buf))
		return -EFAULT;
	else
		return sizeof(int);
}

static int demo_open(struct inode* inode, struct file* filp){
	init_timer(&timer_devp->s_timer);
	timer_devp->s_timer.function = &timer_demo_handler;
	timer_devp->s_timer.expires = jiffies + HZ;

	add_timer(&timer_devp->s_timer);
	atomic_set(&timer_devp->counter, 0);
	return 0;
}
static int demo_release(struct inode* inode, struct file* filp){
	del_timer_sync(&timer_devp->s_timer);
	return 0;
}
static struct file_operations fops=
{
		.owner = THIS_MODULE,
	//	.write = demo_write,
		.read = demo_read,
		.open = demo_open,
		.release = demo_release
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};
static int __init demo_init(void)
{
	int ret=misc_register(&misc);
	timer_devp= kmalloc(sizeof(struct timer_dev), GFP_KERNEL);
	if(!timer_devp){
		misc_deregister(&misc);
		return -ENOMEM;
	}else{
		memset(timer_devp, 0, sizeof(struct timer_dev));
	}

	printk(DEVICE_NAME"\tinit.\n");
	return ret;
}

static void __init demo_exit(void)
{
	kfree(timer_devp);
	misc_deregister(&misc);

	printk(DEVICE_NAME"\texit.\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");

