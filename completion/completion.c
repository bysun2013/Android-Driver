/*
 * completion.c
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

#define DEVICE_NAME "completion"

static struct completion cpt;
static char data[20];
/*
 * 1: completion wake up all; 0: completion wake up only one.
 * */
static int completion_type=0;

static ssize_t completion_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size=strlen(data);
	printk("read start: completion.done= %d.\n", cpt.done);
	wait_for_completion_interruptible( &cpt );

	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}else{
		printk("read end: completion.done= %d.\n", cpt.done);
	}
	return 0;
}

static ssize_t completion_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	if(copy_from_user(data, buf, count))
		return -EINVAL;

	printk("write start: completion.done= %d.\n", cpt.done);
	if(completion_type==0){
		complete( &cpt );
	}else if(completion_type==1)
		complete_all( &cpt );

	printk("write end: completion.done= %d.\n", cpt.done);

	return count;

}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = completion_write,
		.read = completion_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init completion_init(void)
{
	int ret= misc_register(&misc);
	init_completion( &cpt );
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit completion_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(completion_init);
module_exit(completion_exit);

module_param(completion_type,int, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
