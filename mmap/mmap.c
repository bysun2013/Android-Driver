/*
 * mmap.c
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
#include <linux/mm.h>


#define DEVICE_NAME "mmap"

#define BUFFER_SIZE 4096*2
static char *buffer;

static void demo_vma_open(struct vm_area_struct *vma)
{
	printk("VMA open.\n");
}

static void demo_vma_close(struct vm_area_struct *vma)
{
	printk("VMA close.\n");
}

static struct vm_operations_struct remap_vm_ops=
{
		.open = demo_vma_open,
		.close = demo_vma_close
};

static int demo_mmap(struct file* filp, struct vm_area_struct *vma){
	unsigned long physics = virt_to_phys((void*) (unsigned long)buffer);
	unsigned long mypfn = physics >>PAGE_SHIFT;
	unsigned long vmsize = vma->vm_end - vma->vm_start;

	printk("mmap called.\n");

	if(vmsize >BUFFER_SIZE)
		return -EINVAL;
	vma->vm_ops = &remap_vm_ops;
	vma->vm_flags |= VM_RESERVED;
	demo_vma_open(vma);

	if(remap_pfn_range(vma, vma->vm_start, mypfn, vmsize, vma->vm_page_prot));
		return -EAGAIN;

	return 0;
}
static struct file_operations fops=
{
		.owner = THIS_MODULE,
		.mmap = demo_mmap
};

static struct miscdevice misc=
{
		.minor = MISC_DYNAMIC_MINOR,
		.name = DEVICE_NAME,
		.fops = &fops
};

static int __init demo_init(void)
{
	int ret;
	struct page *page;
	ret=misc_register(&misc);
	buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	for(page=virt_to_page(buffer);page<virt_to_page(buffer+BUFFER_SIZE);page++)
		SetPageReserved(page);
	memset(buffer, 0, BUFFER_SIZE);
	strcpy(buffer, "mmap shared success!\n");

	printk(DEVICE_NAME"\tinit.\n");
	return ret;
}

static void __init demo_exit(void)
{
	struct page *page;
	misc_deregister(&misc);
	for(page=virt_to_page(buffer);page<virt_to_page(buffer+BUFFER_SIZE);page++)
		ClearPageReserved(page);

	kfree(buffer);
	printk(DEVICE_NAME"\texit.\n");
}

module_init(demo_init);
module_exit(demo_exit);
MODULE_LICENSE("GPL");


