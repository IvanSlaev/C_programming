#include <linux/module.h>
#include <linux/timer.h>
#include "chardev_macro.h"

static struct timer_list my_timer;

static void my_timer_function(unsigned long ptr)
{
	printk(KERN_INFO "I am in my timer func, jiffies = %ld\n", jiffies);
	printk(KERN_INFO "I think my current task pid is %d\n", (int)current->pid);
	printk(KERN_INFO "my data is: %d\n", (int)ptr);
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	static int len = 100;
	printk(KERN_INFO "Entering the write function\n");
	printk(KERN_INFO "my current task pid is %d\n", (int)current->pid);
	
	init_timer(&my_timer); // initialize
	my_timer.function = my_timer_function;
	my_timer.expires = jiffies + HZ; // 1 second delay
	// my_timer.data = (void*) len;
	my_timer.data = len;
	printk(KERN_INFO "Adding timer at jiffies = %ld\n", jiffies);
	add_timer(&my_timer);
	len += 100;
	return lbuf;
}

static const struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.read = my_generic_read,
	.write = my_write,
	.open = my_generic_open,
	.release = my_generic_release,
};

static void __exit my_exit(void)
{
	// delete any running timers
	printk(KERN_INFO "Delete timer rc = %d\n", del_timer_sync(&my_timer));
	my_generic_exit();
}

module_init(my_generic_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
