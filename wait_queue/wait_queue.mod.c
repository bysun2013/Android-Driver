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
	{ 0x8ddb8b73, "misc_deregister" },
	{ 0xf432dd3d, "__init_waitqueue_head" },
	{ 0x9d101aaa, "misc_register" },
	{ 0xcf21d241, "__wake_up" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xfa66f77c, "finish_wait" },
	{ 0x5c8b5ce8, "prepare_to_wait" },
	{ 0x1000e51, "schedule" },
	{ 0x5cfd1e71, "current_task" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A9F911CF21077D463C010D6");
