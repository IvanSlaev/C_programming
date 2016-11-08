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
	{ 0x7af4f91b, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x9b1b72a7, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8d269047, __VMLINUX_SYMBOL_STR(my_mutex) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lab1_mutex1";


MODULE_INFO(srcversion, "EC8F2E1A03DCC5D98283169");
