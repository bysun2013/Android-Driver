/*
 * spin_lock.c
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

#define DEVICE_NAME "spin_lock"

static char flag = 1;
static char *data ="read\n";
static DEFINE_SPINLOCK(lock);

static ssize_t spin_lock_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);
	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}
	if(flag){
		flag=0;
		if(spin_trylock(&lock)){
			mdelay(15000);
			spin_unlock(&lock);
		}else
			return -EBUSY;
		return size;
	}else{
		flag=1;
		return 0;
	}
}

static ssize_t spin_lock_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	char data[10];
	memset(data, 0, 10);
	if(copy_from_user(data, buf, count))
		return -EINVAL;

	if(strcmp("lock\n", data)==0){
		spin_lock(&lock);
		printk("spin lock available.\n");
		spin_unlock(&lock);
	}else if(strcmp("trylock\n", data)==0){
		if(spin_trylock(&lock)){
			printk("spin lock available.\n");
			spin_unlock(&lock);
		}else{
			printk("spin trylock is not available.\n");
			return -EBUSY;
		}
	}
	return count;
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = spin_lock_write,
		.read = spin_lock_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init spin_locks_init(void)
{
	int ret= misc_register(&misc);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit spin_locks_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(spin_locks_init);
module_exit(spin_locks_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
