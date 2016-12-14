#include <linux/module.h>
#include <linux/init.h>
#include <linux/netdevice.h>

static int __init my_init(void)
{
	struct net_device *dev;
	printk(KERN_INFO "Hello from module loaded at 0x%p\n", my_init);
	dev = first_net_device(&init_net);
	printk(KERN_INFO "dev_base address: 0x%p\n", dev);
	while (dev) 
	{
		printk(KERN_INFO "name = %6s\n", dev->name);
		dev = next_net_device(dev);
	}
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
