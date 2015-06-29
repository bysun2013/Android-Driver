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
	{ 0x7a616134, "kmem_cache_destroy" },
	{ 0xaa798342, "kmem_cache_free" },
	{ 0x27e1a049, "printk" },
	{ 0xe63b4112, "kmem_cache_alloc" },
	{ 0x670380fd, "kmem_cache_create" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "752B6DDFCAC95985AD6DECA");
