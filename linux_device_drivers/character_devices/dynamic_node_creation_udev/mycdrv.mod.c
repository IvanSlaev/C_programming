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
	{ 0xadaba81c, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x197efc3f, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xe7d06ec4, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x6edce356, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x7c3ce4ee, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xa579446d, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x54a74543, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xcf6004e, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xfa474f39, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x4dc3325b, __VMLINUX_SYMBOL_STR(module_refcount) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "01F2B7AF0E34D88038086F6");
