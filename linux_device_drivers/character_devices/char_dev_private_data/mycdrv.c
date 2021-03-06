#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DEATH(mess) { perror(mess); exit(errno); }
#define MYDEV "mycdev"
#define KBUF_SIZE (size_t)(10 + PAGE_SIZE)

static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

static int my_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	char *kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	file->private_data = kbuf;

	printk(KERN_INFO " attempting to open devise %s:\n", MYDEV);
	printk(KERN_INFO " MAJOR number: %d, MINOR number: %d\n", imajor(inode), iminor(inode));
	counter++;
	
	printk(KERN_INFO "%s %s\n", "Successfully opened device:", MYDEV);
	printk(KERN_INFO "%s %d %s\n", "I have been opened", counter, "times since being loaded");
	printk(KERN_INFO "%s%d\n", "ref=", module_refcount(THIS_MODULE));

	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	char *kbuf = file->private_data;
	printk(KERN_INFO "%s%s\n", "Closing device: ", MYDEV);
	printk(KERN_INFO "%s\n", "Freeing private data");
	if (kbuf) 
	{
		kfree(kbuf);
	}
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;
	int nbytes = lbuf - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;
	printk(KERN_INFO "\n READING nbytes:%d, position: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static ssize_t my_write(struct file *file,const char __user *buf, size_t lbuf, loff_t *ppos)
{
	char *kbuf = file->private_data;
	int nbytes = lbuf - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;
	printk(KERN_INFO "\n WRITING nbytes:%d, position: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
};

static int __init my_init(void)
{
	first = MKDEV(my_major, my_minor);
	if (register_chrdev_region(first, count, MYDEV) < 0) 
	{
		printk(KERN_ERR "%s\n", "failed to registed character device region");
		return -1;
	}
	if (!(my_cdev = cdev_alloc())) 
	{
		printk(KERN_ERR "%s\n", "cdev_alloc() failed");
		unregister_chrdev_region(first, count);
		return -1;
	}	
	cdev_init(my_cdev, &my_fops);
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		printk(KERN_ERR "%s\n", "cdev_add failed");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		return -1;
	}
	printk(KERN_INFO "%s%s\n", "Character device registered successfully: ", MYDEV);
	return 0;
}

static void __exit my_exit(void)
{
	if (my_cdev) 
	{
		cdev_del(my_cdev);
	}
	unregister_chrdev_region(first, count);
	printk(KERN_INFO "%s\n", "DEVICE UNREGISTERED");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("THANKS TO JERRY COOPERSTEIN");
MODULE_LICENSE("GPL v2");
