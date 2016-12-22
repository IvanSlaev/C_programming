#include <linux/module.h>
#include <linux/init.h>

static void __exit my_exit(void)
{
	printk(KERN_INFO "Bye, this is the exit func\n");
}

module_exit(my_exit);

MODULE_AUTHOR("Ivan Slaev)");
MODULE_LICENSE("GPL");
