#ifndef _LAB_CHAR_H
#define _LAB_CHAR_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define MYDEV "mycdrv"

static struct class *foo_class;

static char *ramdisk;
static size_t ramdisk_size = (4 * PAGE_SIZE);
static dev_t first;
static unsigned int count = 1;
static struct cdev *my_cdev;
static const struct file_operations my_fops;

static inline int my_generic_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	printk(KERN_INFO "attempting to open device: %s\n", MYDEV);
	printk(KERN_INFO "MAJOR: %d, MINOR: %d\n", imajor(inode), iminor(inode));
	counter++;
	printk(KERN_INFO "Device opened: %s\n", MYDEV);
	printk(KERN_INFO "Opened %d times\n", counter);
	printk(KERN_INFO "REF: %d\n", module_refcount(THIS_MODULE));
	return 0;
}

static inline int my_generic_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Closing: %s\n", MYDEV);
	return 0;
}

static inline ssize_t my_generic_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = ramdisk_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0) 
	{
		printk(KERN_INFO "Reached end of th device on a read\n");
	}
	nbytes = bytes_to_do - copy_to_user(buf, ramdisk + *ppos, bytes_to_do);
	*ppos += nbytes;
	printk(KERN_INFO "Leavind READ, nbytes: %d, pos: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static inline ssize_t my_general_write(struct file *file, char __user buf, size_t lbuf, loff_t *ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = ramdisk_size - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0) 
	{
		printk(KERN_INFO "Reached end of file on WRITE\n");
	}
	nbytes = bytes_to_do - copy_from_user(ramdisk + *ppos, &buf, bytes_to_do);
	*ppos += nbytes;
	printk(KERN_INFO "Leaving the WRITE, nbytes: %d, pos: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static inline loff_t my_generic_lseek(struct file *file, loff_t offset, int orig)
{
	loff_t testpos;
	switch (orig) 
	{
		case SEEK_SET:
			testpos = offset;
			break;
		case SEEK_CUR:
			testpos = file->f_pos + offset;
			break;
		case SEEK_END:
			testpos = ramdisk_size + offset;
			break;
		default:
			return -EINVAL;
	}
	testpos = testpos < ramdisk_size ? testpos : ramdisk_size;
	testpos = testpos >= 0 ? testpos : 0;
	file->f_pos = testpos;
	return testpos;
}

static inline int __init my_generic_init(void)
{
	if (alloc_chrdev_region(&first, 0, count, MYDEV) < 0) 
	{
		printk(KERN_INFO "Region allocation failed\n");
		return -1;
	}
	if (!(my_cdev = cdev_alloc())) 
	{
		printk(KERN_INFO "cdev_alloc() failed\n");
		unregister_chrdev_region(first, count);
		return -1;
	}
	cdev_init(my_cdev, &my_fops);
	ramdisk = kmalloc(ramdisk_size, GFP_KERNEL);
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		printk(KERN_INFO "cdev_add() failed\n");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		kfree(ramdisk);
		return -1;
	}
	foo_class = class_create(THIS_MODULE, "my_class");
	device_create(foo_class, NULL, first, "%s", "mycdrv");
	printk(KERN_INFO "Succeeded in registering character device %s\n", MYDEV);
	printk(KERN_INFO "Major: %d, Minor: %d\n", MAJOR(first), MINOR(first));
	return 0;
}

static inline void __exit my_generic_exit(void)
{
	device_destroy(foo_class, first);
	class_destroy(foo_class);
	if (my_cdev) 
	{
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, count);
	kfree(ramdisk);
	printk(KERN_INFO "device unregidtered\n");
}

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");

#endif
