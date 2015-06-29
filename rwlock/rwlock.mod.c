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
	{ 0x35b6b772, "param_ops_charp" },
	{ 0x8ddb8b73, "misc_deregister" },
	{ 0x9d101aaa, "misc_register" },
	{ 0xc01cf848, "_raw_read_lock" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xd52bf1ce, "_raw_spin_lock" },
	{ 0x7f658e80, "_raw_write_lock" },
	{ 0xadaabe1b, "pv_lock_ops" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x27e1a049, "printk" },
	{ 0x4f68e5c9, "do_gettimeofday" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "5315C171CEF63A1031E257F");
