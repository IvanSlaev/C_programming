#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/firmware.h>

#define MY_FIRM "my_firm"

static const struct firmware *fw;

static void my_release(struct device *dev)
{
	printk(KERN_INFO "I was released %s\n", dev_name(dev));
}

static struct device dev = {
	.release = my_release
};
	
static int __init my_init(void)
{
	const char *fname = MY_FIRM;

	if (dev_set_name(&dev, "%s", "my_dev") < 0) 
	{
		printk(KERN_INFO "Failed setting device name\n");
		return -1;
	}
	printk(KERN_INFO "Success in setting the device name\n");
	if (device_register(&dev) < 0) 
	{
		printk(KERN_INFO "Failed registering %s\n", dev_name(&dev));
		return -1;
	}
	printk(KERN_INFO "Success in registering %s\n", dev_name(&dev));
	if (request_firmware(&fw, fname, &dev) < 0) 
	{
		printk(KERN_INFO "Failed requesting firmware\n");
		device_unregister(&dev);
		return -1;
	}
	printk(KERN_INFO "Success in loading firmware\n");
	printk(KERN_INFO "Content of the firmware %s\n", fw->data);

	return 0;
}

static void __exit my_exit(void)
{
	release_firmware(fw);
	device_unregister(&dev);
	printk(KERN_INFO "Module Exit\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
