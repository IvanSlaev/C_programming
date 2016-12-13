#include <linux/module.h>
#include <linux/init.h>
#include <linux/netdevice.h>

static struct net_device *dev;

static int my_open(struct net_device *dev)
{
	printk(KERN_INFO "In my_open of %s\n", dev->name);

	// starting the transmission queue
	netif_start_queue(dev);
	return 0;
}

static int my_close(struct net_device *dev)
{
	printk(KERN_INFO "In my_close of %s\n", dev->name);

	// starting the transmission queue
	netif_stop_queue(dev);
	return 0;
}

static int stub_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	dev_kfree_skb(skb);
	return 0;
}

	static struct net_device_ops ndo = {
		.ndo_open = my_open,
		.ndo_stop = my_close,
		.ndo_start_xmit = stub_start_xmit
	};

static void my_setup(struct net_device *dev)
{
	int i;
	printk(KERN_INFO "In my_setup of %s\n", dev->name);

	// Fill in the MAC address with a phoney
	for (i = 0; i < ETH_ALEN; ++i) 
	{
		dev->dev_addr[i] = (char)i;
	}

	ether_setup(dev);

	dev->netdev_ops = &ndo;
}

static int __init my_init(void)
{
	printk(KERN_INFO "Loading stub network module\n");
	dev = alloc_netdev(0, "my_net%d", NET_NAME_ENUM, my_setup);
	if (register_netdev(dev)) 
	{
		printk(KERN_INFO "Failed to register\n");
		free_netdev(dev);
		return -1;
	}
	printk(KERN_INFO "Succeeded in loading %s\n\n", dev_name(&dev->dev));
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Unloading stub network module\n");
	unregister_netdev(dev);
	free_netdev(dev);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Bill Shubert, Jerry Cooperstein, Tatsuo Kawasaki (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
