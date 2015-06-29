#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>

#define DRIVER_NAME "tasklet"
static struct tasklet_struct my_tasklet;

static void tasklet_handler( unsigned long data)
{
	printk(KERN_ALERT"tasklet handler is running!\n");
}

static int __init demo_init(void)
{
	tasklet_init(&my_tasklet, tasklet_handler, 0);
	tasklet_schedule(&my_tasklet);
	printk(DRIVER_NAME"\tinit.\n");
	return 0;
}

static void __init demo_exit(void)
{
	tasklet_kill(&my_tasklet);
	printk(DRIVER_NAME"\texit.\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");

