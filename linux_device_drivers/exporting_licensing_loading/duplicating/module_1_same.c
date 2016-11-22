#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from module 1\n");
	return 0;
}

static void function_in_module_1(void)
{
	printk(KERN_INFO "I am defined in module 1!!!\n");
}

static int var_in_module_1 = 1024;

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye from module 1\n");
}

EXPORT_SYMBOL(function_in_module_1);
EXPORT_SYMBOL(var_in_module_1);

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
