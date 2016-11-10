#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>

#define DEATH(mess) { perror(mess); exit(errno); }
#define MYDEV "mycdev"
#define KBUF_SIZE (size_t)(10 + PAGE_SIZE)

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

static int mycdev_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	printk(KERN_INFO " attempting to open devise %s:\n", MYDEV);
	printk(KERN_INFO " MAJOR number: %d, MINOR number: %d\n", imajor(inode), iminor(inode));
	counter++;

	return 0;
}

static int __init my_init(void)
{
	printk("Hello: module loaded");
	return 0;
}

static void __exit my_exit(void)
{
	printk("Bye: module unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("A GENIUS");
MODULE_LICENSE("GPL v2");
