/*
 * rwlock.c
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

#define DEVICE_NAME "rw_lock"

static char *lock_type = "rw";
static char *data = "read\n";
static DEFINE_SPINLOCK(spinlock);
static DEFINE_RWLOCK(rwlock);

static ssize_t rw_lock_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int size = strlen(data);
	struct timeval tv;
	if(copy_to_user(buf, (void *)data, size)){
		return -EINVAL;
	}

	do_gettimeofday(&tv);
	printk("read: start sec: %ld\n", tv.tv_sec);
	if(strcmp("rw", lock_type)==0){
		read_lock(&rwlock);
	}else if(strcmp("spin", lock_type)==0){
		spin_lock(&spinlock);
	}

	do_gettimeofday(&tv);
	printk("read: end sec: %ld\n", tv.tv_sec);
	mdelay(5000);

	if(strcmp("rw", lock_type)==0){
		read_unlock(&rwlock);
	}else if(strcmp("spin", lock_type)==0){
		spin_unlock(&spinlock);
	}

	return 0;
}

static ssize_t rw_lock_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	struct timeval tv;

	do_gettimeofday(&tv);
	printk("write: start sec: %ld\n", tv.tv_sec);

	if(strcmp("rw", lock_type)==0){
		write_lock(&rwlock);
	}else if(strcmp("spin", lock_type)==0){
		spin_lock(&spinlock);
	}

	do_gettimeofday(&tv);
	printk("write: end sec: %ld\n", tv.tv_sec);
	mdelay(5000);

	if(strcmp("rw", lock_type)==0){
		write_unlock(&rwlock);
	}else if(strcmp("spin", lock_type)==0){
		spin_unlock(&spinlock);
	}

	return count;
}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.write = rw_lock_write,
		.read = rw_lock_read
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init rw_locks_init(void)
{
	int ret= misc_register(&misc);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit rw_locks_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(rw_locks_init);
module_exit(rw_locks_exit);

module_param(lock_type, charp, S_IRUGO|S_IWUSR);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
