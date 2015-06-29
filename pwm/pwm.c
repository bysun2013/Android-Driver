/*
 * pwm.c
 *
 *  Created on: Oct 4, 2013
 *      Author: bing
 */
#include "pwm_fun.h"

static unsigned char mem[1];
static struct semaphore lock;

static int s3c6410_pwm_open(struct inode *inode, struct file *filp)
{

	up(&lock);
	return 0;

}

static int s3c6410_pwm_release(struct inode *inode, struct file *filp)
{

	if(!down_trylock(&lock))
		return 0;
	else
		return -EBUSY;

}

static long s3c6410_pwm_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
{
	switch(cmd)
	{
		case PWM_IOCTL_START:
			pwm_start();
			break;

		case PWM_IOCTL_STOP:
		default:
			pwm_stop();
			break;
	}
	return 0;
}

static ssize_t s3c6410_pwm_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{

	unsigned tmp = count;

	memset(mem, 0, 1);

	if(count>1)
		tmp=1;
	printk("Write to /dev/pwm_dev.\n");
	if(copy_from_user(mem, buf, tmp))
	{
		return -EFAULT;
	}else{
		if(mem[0]== '1')
			pwm_start();
		else
			pwm_stop();
	}
	return count;

}

static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.open= s3c6410_pwm_open,
		.release= s3c6410_pwm_release,
		.unlocked_ioctl= s3c6410_pwm_ioctl,
		.write= s3c6410_pwm_write
};

static struct miscdevice misc=
{
		.minor= MISC_DYNAMIC_MINOR,
		.name= DEVICE_NAME,
		.fops= &fops
};

static int __init pwm_init(void)
{
	int ret;

	sema_init(&lock, 1);
	ret=misc_register(&misc);

	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}
static void __exit pwm_exit(void)
{

	misc_deregister(&misc);
	printk(DEVICE_NAME"\texit!\n");
}

module_init(pwm_init);
module_exit(pwm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
