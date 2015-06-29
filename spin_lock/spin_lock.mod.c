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
	{ 0x9d101aaa, "misc_register" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xadaabe1b, "pv_lock_ops" },
	{ 0x27e1a049, "printk" },
	{ 0xe15f42bb, "_raw_spin_trylock" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "AA9ECC0C37918E1E9720622");
