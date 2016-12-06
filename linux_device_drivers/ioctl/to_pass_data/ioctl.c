#include <linux/module.h>
#include "chardev_macro.h"

struct my_data {
	int i;
	long x;
	char s[256];
};

static struct my_data my_data = {
	.i = -100,
	.x = 100,
	.s = "original string"
};

#define MYIOC_TYPE 'k'

static long my_unlocked_ioctl(struct file *fp, unsigned int cmd, unsigned long arg)
{
	int size, rc, direction;
	void __user *ioargp = (void __user *)arg;

	if (_IOC_TYPE(cmd) != MYIOC_TYPE) 
	{
		printk(KERN_INFO "Got invalid case, CMD=%d\n", cmd);
		return -EINVAL;
	}

	direction = _IOC_DIR(cmd);
	size = _IOC_SIZE(cmd);

	switch (direction) 
	{
		case _IOC_WRITE:
			printk(KERN_INFO "Reading %d bytes from user-space and writing to device\n", size);
			rc = copy_from_user(&my_data, ioargp, size);
			printk(KERN_INFO "my_data.i = %d, my_data.x = %d, my_data.s = %s\n", my_data.i, (int)my_data.x, my_data.s);
			return rc;
			break;

		case _IOC_READ:
			printk(KERN_INFO "Reading device and writing %d bytes to user-space\n", size);
			printk(KERN_INFO "my_data.i = %d, my_data.x = %d, my_data.s = %s\n", my_data.i, (int)my_data.x, my_data.s);
			rc = copy_to_user(ioargp, &my_data, size);
			return rc;
			break;
		default:
			printk(KERN_INFO "Got invalid case, CMD=%d\n", cmd);
			return -EINVAL;
	}
}

static const struct file_operations my_fops =  {
	.owner = THIS_MODULE,
	.unlocked_ioctl = my_unlocked_ioctl,
	.open = my_generic_open,
	.release = my_generic_release
};

module_init(my_generic_init);
module_exit(my_generic_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
