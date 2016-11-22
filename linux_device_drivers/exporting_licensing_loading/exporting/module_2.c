#include <linux/module.h>
#include <linux/init.h>

extern void function_in_module_1(void);
extern int var_in_module_1;

static int __init my_init(void)
{
	printk(KERN_INFO "Hello from module 2\n");
	printk(KERN_INFO "Var from module 1 is : %d\n", var_in_module_1);
	printk(KERN_INFO "And calling the function from module 1\n");
	function_in_module_1();
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye from module 2\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
