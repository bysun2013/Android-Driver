/*
 * slab.c
 *
 *  Created on: Oct 15, 2013
 *      Author: bing
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>

#define DEVICE_NAME "slab_demo"

struct data{
	char *name;
	int value;
}*datap;
static struct kmem_cache *cachep;

static int __init demo_init(void)
{
	int ret=0;
	cachep=kmem_cache_create("slab_test", sizeof(*datap), 0, SLAB_PANIC|SLAB_HWCACHE_ALIGN, NULL);
	datap=kmem_cache_alloc(cachep, GFP_KERNEL);
	datap->name="slab_data";
	datap->value =1234;

	printk(DEVICE_NAME"\tinit.\n");
	return ret;
}

static void __init demo_exit(void)
{

	if(datap){
		printk("data.name = %s\n", datap->name);
		printk("data.value =%d\n", datap->value);
		kmem_cache_free(cachep, (void *)datap);
	}
	kmem_cache_destroy(cachep);

	printk(DEVICE_NAME"\texit.\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");


