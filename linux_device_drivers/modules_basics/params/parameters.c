#include <linux/module.h>
#include <linux/init.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static int parameter = 12;
module_param(parameter, int, S_IRUGO | S_IWUSR);

static int __init my_init(void)
{
	printk("%s\n", "Module loaded");
	printk("parameter = %d\n", parameter);
	return 0;	
}

static void __exit my_exit(void)
{
	printk("%s\n", "Module unloaded");
}

module_init(my_init);
module_exit(my_exit);
