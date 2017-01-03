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

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

static int my_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	printk(KERN_INFO " attempting to open devise %s:\n", MYDEV);
	printk(KERN_INFO " MAJOR number: %d, MINOR number: %d\n", imajor(inode), iminor(inode));
	counter++;
	
	printk(KERN_INFO "%s %s\n", "Successfully opened device:", MYDEV);
	printk(KERN_INFO "%s %d %s\n", "I have been opened", counter, "times since being loaded");
	printk(KERN_INFO "%s%d\n", "ref=", module_refcount(THIS_MODULE));

	// uncomment to inhibit seeking
	// file->f_mode = file->f_mode & ~FMODE_LSEEK;

	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "%s%s\n", "Closing device: ", MYDEV);
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = KBUF_SIZE - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0) 
	{
		printk(KERN_INFO "%s\n", "Reached end of the device on read");
	}
	nbytes = maxbytes - copy_to_user(buf, kbuf + *ppos, lbuf);
	*ppos += nbytes;
	printk(KERN_INFO "\n READING nbytes:%d, position: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static ssize_t my_write(struct file *file,const char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = KBUF_SIZE - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0) 
	{
		printk(KERN_INFO "%s\n", "Reached end of the device on write");
	}
	nbytes = bytes_to_do - copy_from_user(kbuf + *ppos, buf, lbuf);
	*ppos += nbytes;
	printk(KERN_INFO "\n WRITING nbytes:%d, position: %d\n", nbytes, (int)*ppos);
	return nbytes;
}

static loff_t my_lseek(struct file *file, loff_t offset, int orig)
{
	loff_t testpos;
	switch (orig) 
	{
		case SEEK_SET:
			testpos = offset;
			break;
		case SEEK_CUR:
			testpos = file->f_pos +  offset;
			break;
		case SEEK_END:
			testpos = KBUF_SIZE + offset;
			break;
		default:
			return -EINVAL;
	}
	testpos = testpos < KBUF_SIZE ? testpos : KBUF_SIZE;
	testpos = testpos >= 0 ? testpos : 0;
	file->f_pos = testpos;
	printk(KERN_INFO "%s%ld\n", "Seeking to pos=", (long)testpos);
	return testpos;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_read,
	.write = my_write,
	.open = my_open,
	.release = my_release,
	.llseek = my_lseek,
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
	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		printk(KERN_ERR "%s\n", "cdev_add failed");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		kfree(kbuf);
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
	if (kbuf) 
	{
		kfree(kbuf);
	}
	unregister_chrdev_region(first, count);
	printk(KERN_INFO "%s\n", "DEVICE UNREGISTERED");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("THANKS TO JERRY COOPERSTEIN");
MODULE_LICENSE("GPL v2");
