/*
 * reserve_mem.c
 *
 *  Created on: Mar 2, 2014
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/io.h>
#include <asm/atomic.h>
#include <asm/uaccess.h>

#define DEVICE_NAME "reserve_memory"

static char* reserve;
EXPORT_SYMBOL_GPL(reserve);
static int __init reserve_mem_init(void)
{
	int ret=0;
    reserve=ioremap(0xb400000,0x2800000);
    iowrite32(20,reserve+4);
	printk(DEVICE_NAME"\tinitialized\n");
	return ret;
}

static void __exit reserve_mem_exit(void)
{


	printk(DEVICE_NAME"\texit!\n");
}

module_init(reserve_mem_init);
module_exit(reserve_mem_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bing");
