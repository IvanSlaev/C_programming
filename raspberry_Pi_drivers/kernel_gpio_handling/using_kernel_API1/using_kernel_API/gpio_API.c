#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init params_init(void)
{
	printk(KERN_INFO "Module Raspberry Pi\n");
	return 0;
}

static void __exit params_exit(void)
{
	printk(KERN_INFO "Goodbye, Module Raspberry Pi\n");
}

module_init(params_init);
module_exit(params_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Slaev");
