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
	{ 0x9813f95c, __VMLINUX_SYMBOL_STR(pci_get_device) },
	{ 0x33c6c741, __VMLINUX_SYMBOL_STR(pci_dev_put) },
	{ 0xd0a4a083, __VMLINUX_SYMBOL_STR(pci_bus_read_config_byte) },
	{ 0xab61760b, __VMLINUX_SYMBOL_STR(pci_bus_read_config_word) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "E327C40CE63A459F6F45C1E");
