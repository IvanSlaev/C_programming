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
	{ 0x5ca86013, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xa202a8e5, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xcda60f48, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xeb793807, __VMLINUX_SYMBOL_STR(send_sig) },
	{ 0x7edd2684, __VMLINUX_SYMBOL_STR(pid_task) },
	{ 0xb7b49be1, __VMLINUX_SYMBOL_STR(find_vpid) },
	{ 0x8e7ff0de, __VMLINUX_SYMBOL_STR(module_refcount) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xab87ecce, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "2C4E8AA8E87ECEFF19DBA5F");
