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
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x8e7ff0de, __VMLINUX_SYMBOL_STR(module_refcount) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x5ca86013, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa202a8e5, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xab87ecce, __VMLINUX_SYMBOL_STR(misc_deregister) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "AD22B1735FC6FB1D79E7BBF");
