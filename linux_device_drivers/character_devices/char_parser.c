#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mm.h>

#define MYDEV "mycdev"
#define KBUF_SIZE 3 * PAGE_SIZE 

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static struct cdev *my_cdev;
static struct class *my_class;

static void my_vma_open(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA open, vm_start %lx\n", vma->vm_start);
}

static void my_vma_close(struct vm_area_struct *vma)
{
	printk(KERN_NOTICE "Simple VMA close.\n");
}

static int my_vma_fault(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	vmf->pgoff = virt_to_phys(kbuf) << PAGE_SHIFT;
	vmf->vm_flags = FAULT_FLAG_NONLINEAR;
	return 0;
}

static const struct vm_operations_struct my_vm_ops = {
	.open = my_vma_open,
	.close = my_vma_close,
	.fault = my_vma_fault,
};

static int my_mmap(struct file *filp, struct vm_area_struct *vma)
{
	vma->vm_flags = VM_IO;
	vma->vm_ops = &my_vm_ops;
	my_vma_open(vma);
	return 0;
}

/*
static void buffer_parser(void) {
	int i;

	for (i = 0; kbuf[i] != '\0' && i < KBUF_SIZE - 1; i++) {
		if (kbuf[i] == 'a') {
			kbuf[i] = 'z';
		}
	}
}
*/

static int my_open(struct inode *inode, struct file *file)
{
	static int counter = 0;
	pr_info(" MAJOR number: %d, MINOR number: %d\n", imajor(inode), iminor(inode));
	counter++;
	
	pr_err("Successfully opened device: %s\n", MYDEV);
	pr_info("I have been opened %d times since being loaded\n", counter);
	
	kbuf = vmalloc(KBUF_SIZE, GFP_KERNEL);	
	memset(kbuf, 'a', KBUF_SIZE);
	kbuf[KBUF_SIZE - 2] = 'E';
	kbuf[KBUF_SIZE - 1] = '\0';

	return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
	pr_info("Closing device: %s\n", MYDEV);
	vfree(kbuf);
	return 0;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_release,
	.mmap = my_mmap,
};

static int __init my_init(void)
{
	if (alloc_chrdev_region(&first, 0, count, MYDEV) < 0)
	{
		pr_err("Region allocation failed\n");
		return -1;
	}
	my_cdev = cdev_alloc();
	if (!my_cdev) 
	{
		pr_err("cdev_alloc() failed\n");
		unregister_chrdev_region(first, count);
		return -ENOMEM;
	}	
	cdev_init(my_cdev, &my_fops);	
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		pr_err("cdev_add failed\n");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		return -1;
	}

	my_class = class_create(THIS_MODULE, "my_class");
	device_create (my_class, NULL, first, "%s", "mycdrv");

	pr_info("Character device registered successfully: %s\n", MYDEV);
	pr_info("Major number: %d, minor number: %d\n", MAJOR(first), MINOR(first));
	return 0;
}

static void __exit my_exit(void)
{
	device_destroy(my_class, first);
	class_unregister(my_class);
	class_destroy(my_class);

	if (my_cdev) 
		cdev_del(my_cdev);
	unregister_chrdev_region(first, count);

	pr_info("DEVICE %s UNREGISTERED\n", MYDEV);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("IVAN SLAEV, THANKS TO JERRY COOPERSTEIN");
MODULE_LICENSE("GPL v2");
