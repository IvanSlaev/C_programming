#include <linux/module.h>
#include <linux/init.h>
#include <linux/usb.h>
#include <linux/slab.h>

struct my_usb_info
{
	int connect_count;
};

static int my_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct my_usb_info *usb_info;

	struct usb_device *dev = interface_to_usbdev(intf);
	static int my_counter = 0;

	printk(KERN_INFO "\nmy_usb_probe\n");
	printk(KERN_INFO "devnum=%d, speed=%d\n", dev->devnum, (int)dev->speed);
	printk(KERN_INFO "idVendor=0x%hX, idProduct=0x%hX, bcdDevice=0x%hX\n", dev->descriptor.idVendor, dev->descriptor.idProduct, dev->descriptor.bcdDevice);
	printk(KERN_INFO "class=0x%hX, subclass=0x%hX\n", dev->descriptor.bDeviceClass, dev->descriptor.bDeviceSubClass);
	printk(KERN_INFO "protocol=0x%hX, packetsize=%hu\n", dev->descriptor.bDeviceProtocol, dev->descriptor.bMaxPacketSize0);
	printk(KERN_INFO "manufacturer=0x%hX, product=0x%hX, serial=0x%hX\n", dev->descriptor.iManufacturer, dev->descriptor.iProduct, dev->descriptor.iSerialNumber);

	usb_info = kmalloc(sizeof(struct my_usb_info), GFP_KERNEL);
	usb_info->connect_count = my_counter++;
	usb_set_intfdata(intf, usb_info);
	printk(KERN_INFO "connect_count=%d\n\n", usb_info->connect_count);
	return 0;
}

static void my_disconnect(struct usb_interface *intf)
{
	struct my_usb_info *usb_info;
	usb_info = usb_get_intfdata(intf);
	printk(KERN_INFO "\nmy_usb_disconnect\n");
	kfree(usb_info);
}

static struct usb_device_id my_usb_table[] = {
	{USB_DEVICE(0x04e8, 0x6860)},
	{}
};

MODULE_DEVICE_TABLE(usb, my_usb_table);

static struct usb_driver my_usb_driver = {
	.name = "usb-hotplug",
	.probe = my_probe,
	.disconnect = my_disconnect,
	.id_table = my_usb_table,
};

static int __init my_init(void)
{
	int err;
	printk(KERN_INFO "Hello USB\n");
	err = usb_register(&my_usb_driver);
	return err;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Goodbye USB\n");
	usb_deregister(&my_usb_driver);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Terry Griffin, Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
