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
	{ 0x37a0cba, "kfree" },
	{ 0x8ddb8b73, "misc_deregister" },
	{ 0x49cdbaea, "kmem_cache_alloc_trace" },
	{ 0x92295a0d, "kmalloc_caches" },
	{ 0x9d101aaa, "misc_register" },
	{ 0xfc04f8ff, "remap_pfn_range" },
	{ 0xe52947e7, "__phys_addr" },
	{ 0x27e1a049, "printk" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E6656656A96C8C5FBA78A7E");
