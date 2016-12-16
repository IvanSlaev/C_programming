#include <linux/module.h>
#include <linux/init.h>
#include <linux/notifier.h>
#include <linux/usb.h>

static int my_call(struct notifier_block *b, unsigned long event, void *pointer)
{
	printk(KERN_INFO "USB event = %ld\n", event);
	switch (event) 
	{
		case USB_DEVICE_ADD:
			printk(KERN_INFO "USB device was added\n");
			break;
		case USB_DEVICE_REMOVE:
			printk(KERN_INFO "USB device was removed\n");
			break;
		case USB_BUS_ADD:
			printk(KERN_INFO "USB bus was added\n");
			break;
		case USB_BUS_REMOVE:
			printk(KERN_INFO "USB bus was removed\n");
			break;
		default:
			printk(KERN_INFO "Unknowen USB event: %ld\n", event);
			break;
	}

	return NOTIFY_OK;
}

static struct notifier_block my_nh_block = {
	.notifier_call = my_call,
	.priority = 0
};

static int __init my_init(void)
{
	usb_register_notify(&my_nh_block);
	printk(KERN_INFO "USB notifier loaded\n");
	return 0;
}

static void __exit my_exit(void)
{
	usb_unregister_notify(&my_nh_block);
	printk(KERN_INFO "USB notifuer unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
