#include <linux/module.h>
#include <linux/init.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static int __init my_init(void)
{
	printk("Hello: module loaded");
	return 0;
}

static void __exit my_exit(void)
{
	printk("Bye: module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_LICENSE("GPL v2");
