#include <linux/module.h>
#include <linux/init.h>
#include <linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/fs.h>

void force()
{
}
static int rm_init(void)
{
	struct module *mod = (struct module*)0xf88de380;
	int i;
	int o=0;
	mod->state = MODULE_STATE_LIVE; //为了卸载能进行下去，也就是避开情况1，将模块的状态改变为LIVE
	
	/*	由于是模块的exit导致了无法返回，则替换mod的exit。
	再次调用rmmod的时候会调用到sys_delete_module，最后会调用 exit回调函数，
	新的exit当然不会阻塞，成功返回，进而可以free掉module	
	*/
	//mod->exit = force;
	for (i = 0; i < NR_CPUS; i++)
	{ 		//将引用计数归0
		mod->ref[i].count = *(local_t *)&o;
	}
	return 0;
}
static void __exit rm_exit(void)
{
}  
module_init(rm_init);  
module_exit(rm_exit);  
MODULE_LICENSE("GPL");  
