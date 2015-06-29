/*
 * atomic.c
 *
 *  Created on: Oct 6, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/atomic.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "atomic"

/*  atomic 驱动层参数变量
 *  0：多个进程可以打开/dev/atomic设备文件
 *  1：只有一个进程可以打开/dev/atomic设备文件
*/
static int atom = 0;

static atomic_t atomic_var = ATOMIC_INIT(1);

static int atomic_open(struct inode *node, struct file* file)
{
	if(atom)
	{
		if(!atomic_dec_and_test(&atomic_var)){
			atomic_inc(&atomic_var);
			return -EBUSY;
		}
	}
	return 0;
}

static int atomic_release(struct inode *node, struct file* file)
{
	if(atom)
	{
			atomic_dec(&atomic_var);
	}
	return 0;
}

static struct file_operations fops={
		.owner = THIS_MODULE,
		.release= atomic_release,
		.open= atomic_open
};

static struct miscdevice misc={
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init atomic_init(void)
{
	int ret;

	ret= misc_register(&misc);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}
static void __exit atomic_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(atomic_init);
module_exit(atomic_exit);

module_param(atom, int, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");


