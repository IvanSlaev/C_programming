#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>

#define MYDEV_NAME "mucdrv"
#define KBUF_SIZE (size_t)(PAGE_SIZE)
#define MAXIRQS 256
#define NCOPY (MAXIRQS * sizeof(int))

static char *kbuf;
static dev_t first;
static unsigned int count = 1;
static int my_major = 700, my_minor = 0;
static struct cdev *my_cdev;

static int *interrupts;

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	interrupts[irq]++;
	return 0;
}

static void freeup_irqs(void)
{
	int irq;
	for (irq = 0; irq < MAXIRQS; irq++) 
	{
		if (interrupts[irq] >= 0) 
		{
			synchronize_irq(irq);
			printk(KERN_INFO "Freeing IRQ: %4d, which had %10d events\n", irq, interrupts[irq]);
			free_irq(irq, interrupts);
		}
	}
}

static ssize_t my_read(struct file *file, char __user *buf, size_t lbuf, loff_t *ppos)
{
	int nbytes, maxbytes, bytes_to_do;
	maxbytes = KBUF_SIZE - *ppos;
	bytes_to_do = maxbytes > lbuf ? lbuf : maxbytes;
	if (bytes_to_do == 0) 
	{
		printk(KERN_INFO "Reached end of the device on read\n");
	}
	nbytes = bytes_to_do - copy_to_user(buf, kbuf + *ppos, bytes_to_do);
	*ppos += nbytes;
	return nbytes;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_read,
};

static int __init my_init(void)
{
	int irq;
	first = MKDEV(my_major, my_minor);

	if (register_chrdev_region(first, count, MYDEV_NAME) < 0) 
	{
		printk(KERN_INFO "failed to register region\n");
		return -1;
	}

	if (!(my_cdev = cdev_alloc())) 
	{
		printk(KERN_INFO "failed to allocate\n");
		return -1;
	}

	cdev_init(my_cdev, &my_fops);
	kbuf = kmalloc(KBUF_SIZE, GFP_KERNEL);
	if (cdev_add(my_cdev, first, count) < 0) 
	{
		printk(KERN_INFO "cdev_add() failed\n");
		cdev_del(my_cdev);
		unregister_chrdev_region(first, count);
		kfree(kbuf);
		return -1;
	}

	printk(KERN_INFO "Charachter device registered successfully\n");
	printk(KERN_INFO "MAJOR: %d, MINOR: %d\n", MAJOR(first), MINOR(first));
	interrupts = (int *)kbuf;

	for (irq = 0; irq < MAXIRQS; irq++) 
	{
		interrupts[irq] = -1;
		if (!request_irq(irq, my_interrupt, IRQF_SHARED, "my_int", interrupts)) 
		{
			interrupts[irq] = 0;
			printk(KERN_INFO "IRQ: %d registered\n", irq);
		}
	}

	return 0;
}

static void __exit my_exit(void)
{
	freeup_irqs();
	cdev_del(my_cdev);
	unregister_chrdev_region(first, count);
	kfree(kbuf);
	printk(KERN_INFO "Device UNREGISTERED\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
