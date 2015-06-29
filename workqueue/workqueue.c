/*
 * workqueue.c
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

#define DRIVER_NAME "workqueue"
static struct workqueue_struct *my_wq;
struct work_struct_data{
	struct work_struct work;
	void *data;
}*ws_data;

static void work_handler(struct work_struct *work)
{
	struct work_struct_data *wsdata=(struct work_struct_data *)work;

	printk(KERN_ALERT"work_handler data:%s.\n", (char *)wsdata->data);
}

static int __init demo_init(void)
{
	int ret= 0;

	my_wq = create_workqueue("my_wq");
	if(my_wq){
		ws_data = (struct work_struct_data *)kmalloc(sizeof(struct work_struct_data), GFP_KERNEL);

		ws_data->data = (char *)"hello, world";
		if(ws_data){
			INIT_WORK(&ws_data->work, work_handler);
			ret= queue_work(my_wq, &ws_data->work);
		}else
			ret = -1;
	}else
		ret = -1;

	printk(DRIVER_NAME"\tinit.\n");
	return ret;
}

static void __init demo_exit(void)
{
	flush_workqueue(my_wq);
	destroy_workqueue(my_wq);

	printk(DRIVER_NAME"\texit.\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");

