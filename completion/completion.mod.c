#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa8a0d3ac, "module_layout" },
	{ 0x15692c87, "param_ops_int" },
	{ 0x8ddb8b73, "misc_deregister" },
	{ 0xf432dd3d, "__init_waitqueue_head" },
	{ 0x9d101aaa, "misc_register" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x15ddbdc, "wait_for_completion_interruptible" },
	{ 0x40256835, "complete_all" },
	{ 0x4b06d2e7, "complete" },
	{ 0x27e1a049, "printk" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "FEEBA8CEC7E0CF43817C3A5");
