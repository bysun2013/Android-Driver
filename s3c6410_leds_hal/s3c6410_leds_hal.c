/*
 * s3c6410_leds_hal.c
 *
 *  Created on: Oct 18, 2013
 *      Author: bing
 */

#include "s3c6410_leds_hal.h"
#include "leds_hal_define.h"

static int major= S3C6410_LEDS_MAJOR;
static int minor= S3C6410_LEDS_MINOR;
static dev_t dev_number;

static unsigned char mem[5];
static struct cdev leds_cdev;
static struct class *leds_class = NULL;


static int bytes_to_int(unsigned char buf[], int start){
	int n = 0;
	n = ((int) buf[start]<<24 |(int) buf[start+1]<<16 | (int) buf[start+2]<<8 | (int) buf[start+3]);
	return n;
}

static void int_to_bytes(int n, unsigned char buf[], int start){

	buf[start]= n >>24;
	buf[start+1] = n >>16;
	buf[start+2] = n >>8;
	buf[start+3] = n;

}

static ssize_t s3c6410_leds_write(struct file* filp, const char __user *buf, size_t count, loff_t *ppos)
{
	if(copy_from_user(mem, buf, 5))
		return -EFAULT;
	else{
		int gpm_type = mem[0];
		switch(gpm_type){
		case S3C6410_LEDS_HAL_WRITE_GPMCON:
			iowrite32(bytes_to_int(mem, 1), S3C64XX_GPKCON);
			break;
		case S3C6410_LEDS_HAL_WRITE_GPMDAT:
			iowrite32(bytes_to_int(mem, 1), S3C64XX_GPKDAT);
			break;
		}
	}
	return 5;
}

static ssize_t s3c6410_leds_read(struct file* filp, char __user *buf, size_t count, loff_t *ppos)
{
	int gpm_type = mem[0];
	int gpm_value = 0;

	switch(gpm_type){
	case S3C6410_LEDS_HAL_READ_GPMCON:
		gpm_value = ioread32(S3C64XX_GPKCON);
		break;
	case S3C6410_LEDS_HAL_READ_GPMDAT:
		gpm_value = ioread32(S3C64XX_GPKDAT);
		break;
	default:
		printk("argument is wrong!\n");
		return count;
	}

	int_to_bytes(gpm_value, mem, 1);
	if(copy_to_user(buf, (void *)mem, 5))
		return -EFAULT;

	return 5;
}
static struct file_operations fops={
		.owner = THIS_MODULE,
		.read= s3c6410_leds_read,
		.write= s3c6410_leds_write
};


/* Create device file */
static int leds_create_device(void)
{
	int ret=0;
	int err=0;

	cdev_init(&leds_cdev, &fops);
	leds_cdev.owner = THIS_MODULE;

	if(major == 0){
		err=alloc_chrdev_region(&leds_cdev.dev, 10, S3C6410_LEDS_COUNT, DEVICE_NAME);
		if(err < 0){
			printk(KERN_WARNING"alloc_chrdev_region() failed! \n");
			return err;
		}
		major=MAJOR(leds_cdev.dev);
		minor=MINOR(leds_cdev.dev);
		dev_number=leds_cdev.dev;

	}else{
		dev_number=MKDEV(major, minor);
		err = register_chrdev_region(dev_number, S3C6410_LEDS_COUNT, DEVICE_NAME);
		if(err < 0){
			printk(KERN_WARNING"register_chrdev_region() failed! \n");
			return err;
		}
	}
	ret=cdev_add(&leds_cdev, dev_number,S3C6410_LEDS_COUNT);
	leds_class=class_create(THIS_MODULE, DEVICE_NAME);
	device_create(leds_class, NULL, dev_number, NULL, DEVICE_NAME);
	return ret;
}

static void leds_destroy_device(void)
{
//When rmmod is executed, it crash....
	unregister_chrdev_region(dev_number, S3C6410_LEDS_COUNT);
	device_destroy(leds_class, dev_number);
	if(leds_class)
		class_destroy(leds_class);

}

static int __init leds_init(void)
{
	int ret;

	ret=leds_create_device();
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}
static void __exit leds_exit(void)
{

	leds_destroy_device();
	printk(DEVICE_NAME"\texit!\n");
}

module_init(leds_init);
module_exit(leds_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
