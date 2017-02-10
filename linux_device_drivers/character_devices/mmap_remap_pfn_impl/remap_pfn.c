#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mm.h>

#define MYDEV "mycdev"
#define MAX_SIZE PAGE_SIZE

static char *kbuf;
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

static int my_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	counter++;
	pr_info("Attempting to open devise %s:\n", MYDEV);
	pr_info("MAJOR number: %d, MINOR number: %d\n", imajor(inode), iminor(inode));	
	pr_info("Successfully opened device: %s, for the %d time\n", MYDEV, counter);

	kbuf = kmalloc(MAX_SIZE, GFP_KERNEL);
	memset(kbuf, '\0', MAX_SIZE);

	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("Closing device: %s\n", MYDEV);

	kfree(kbuf);

	return 0;
}

static void my_vma_open(struct vm_area_struct *vma)
{
	pr_info("VMA open, vma->start: %lx\n", vma->vm_start);
}

static void my_vma_close(struct vm_area_struct *vma)
{
	pr_info("VMA close\n");
}

static const struct vm_operations_struct my_vma_ops = {
	.open = my_vma_open,
	.close = my_vma_close,
};

static int my_mmap(struct file *file, struct vm_area_struct *vma)
{
	unsigned long pfn;

	if ((vma->vm_end - vma->vm_start) > MAX_SIZE) {
		pr_err("You cannot mmap more than kernel buffer size, mapping size will be reduced");
		vma->vm_end = vma->vm_start + MAX_SIZE; 
	}

	pfn = page_to_pfn(virt_to_page(kbuf));
	if (remap_pfn_range(vma, vma->vm_start, pfn, vma->vm_end - vma->vm_start, vma->vm_page_prot))
		return -EAGAIN;

	vma->vm_ops = &my_vma_ops;
	my_vma_open(vma);
	return 0;
}

static int my_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	parse_buffer();
	return 0;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.mmap = my_mmap,
	.fsync = my_fsync,
	.release = my_release,
};

static int __init my_init(void)
{
	if (alloc_chrdev_region(&first, 0, count, MYDEV) < 0)
	{
		pr_info("Region allocation failed\n");
		return -1;
	}

	if (!(my_cdev = cdev_alloc())) 
	{
		pr_err("cdev_alloc() failed\n");
		unregister_chrdev_region(first, count);
		return -1;
	}	
	cdev_init(my_cdev, &my_fops);
	
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		pr_err("cdev_add failed\n");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		kfree(kbuf);
		return -1;
	}

	my_class = class_create(THIS_MODULE, "my_class");
	device_create (my_class, NULL, first, "%s", "mycdrv");

	pr_info("Character device registered successfully: %s", MYDEV);
	pr_info("Major number: %d, Minor number: %d\n", MAJOR(first), MINOR(first));
	return 0;
}

static void __exit my_exit(void)
{
	device_destroy(my_class, first);
	class_unregister(my_class);
	class_destroy(my_class);
	unregister_chrdev_region(first, count);
	pr_info("DEVICE UNREGISTERED\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("IVAN SLAEV");
MODULE_LICENSE("GPL");
