#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
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
	{ 0x141d70f7, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x321b8f70, __VMLINUX_SYMBOL_STR(hrtimer_forward) },
	{ 0x54b31163, __VMLINUX_SYMBOL_STR(hrtimer_start) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xf4b6c232, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0xc9053c8d, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x884c7ac4, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf8c2d66, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "56A083CC4C32D7B23D0C2EE");
