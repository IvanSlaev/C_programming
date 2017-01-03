#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
	printk(KERN_INFO "Hello, this is the init func\n");
	return 0;
}

module_init(my_init);

MODULE_AUTHOR("Ivan Slaev");
MODULE_LICENSE("GPL");
