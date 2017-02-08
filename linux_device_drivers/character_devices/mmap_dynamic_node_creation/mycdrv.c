#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <sys/mman.h>

#define MYDEV "mycdev"
#define MAX_SIZE 33

static char kbuf[MAX_SIZE];
static dev_t first;
static unsigned int count = 1;
static struct cdev *my_cdev;
static struct class *my_class; 

static void parse_buffer(void)
{
	int i;

	for (i = 0; kbuf[i] != '\0' && i < MAX_SIZE - 1; i++) {
		if (kbuf[i] == 'a') {
			kbuf[i] = 'z';
		}
	}
}

static int simple_nopage_mmap(struct file *filp, struct vm_area_struct *vma)
{
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	if (offset >= __pa(high_memory) || (filp->f_flags & O_SYNC))
		vma->vm_flags |= VM_IO;

	vma->vm_flags |= VM_RESERVED;
	vma->vm_ops = &simple_nopage_vm_ops;
	simple_vma_open(vma);
	return 0;
}

static void my_vm_open(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA open, virt %lx, phys %lx\n", vma->vm_start, vma->vm_pgoff << PAGE_SHIFT);
}

static void my_vm_close(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA close.\n");
}

static struct *my_nopage(struct vm_area_struct *vma, unsigned long address, int *type)
{
	struct page *pageptr;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long physaddr = address - vma->vm_start + offset;
	unsigned long pageframe = physaddr >> PAGE_SHIFT;

	if (!pfn_valid(pageframe))
		return NOPAGE_SIGBUS;
	pageptr = pfn_to_page(pageframe);
	get_page(pageptr);
	if (type)
		*type = VM_FAULT_MINOR;
	return pageptr;
}

static struct vm_operations_struct vm_ops = {
	.open = my_vm_open,
	.close = my_vm_close,
	.nopage = my_nopage,
};

static int my_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
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
	printk(KERN_INFO "%s%s\n", "Closing device: ", MYDEV);
	return 0;
}

static ssize_t my_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes;

	nbytes = copy_to_user(buf, kbuf, MAX_SIZE - 1);
	printk(KERN_INFO "\n READING nbytes:%d, kbuf %s\n", nbytes, kbuf);
	return nbytes;
}

static ssize_t my_write(struct file *file,const char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes;

	if (lbuf > MAX_SIZE - 1)
		pr_info("User message is longer than 32 characters. The chars after the 32th one will be discarted"); 

	nbytes = copy_from_user(kbuf, buf, MAX_SIZE - 1);	
	printk(KERN_INFO "\n WRITING nbytes:%d, position: %d\n", nbytes, (int)*ppos);
	parse_buffer();
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
	memset(kbuf, '\0', MAX_SIZE);

	if (alloc_chrdev_region(&first, 0, count, MYDEV) < 0)
	{
		printk(KERN_INFO "Region allocation failed\n");
		return -1;
	}

	if (!(my_cdev = cdev_alloc())) 
	{
		printk(KERN_ERR "%s\n", "cdev_alloc() failed");
		unregister_chrdev_region(first, count);
		return -1;
	}	
	cdev_init(my_cdev, &my_fops);
	memset(kbuf, '\0', 30);
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		printk(KERN_ERR "%s\n", "cdev_add failed");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		kfree(kbuf);
		return -1;
	}

	my_class = class_create(THIS_MODULE, "my_class");
	device_create (my_class, NULL, first, "%s", "mycdrv");

	printk(KERN_INFO "%s%s\n", "Character device registered successfully: ", MYDEV);
	printk(KERN_INFO "%s%d%s%d\n", "Major number:", MAJOR(first), " minor number:", MINOR(first));
	return 0;
}

static void __exit my_exit(void)
{
	device_destroy(my_class, first);
	class_unregister(my_class);
	class_destroy(my_class);
	unregister_chrdev_region(first, count);
	printk(KERN_INFO "%s\n", "DEVICE UNREGISTERED");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("THANKS TO JERRY COOPERSTEIN");
MODULE_LICENSE("GPL v2");
