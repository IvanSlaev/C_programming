#include <linux/module.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include "chardev_macro.h"

static atomic_t ntimers;

struct my_dat {
	int l;
	struct timer_list *tl; 	
};

static void my_timer_function(unsigned long ptr)
{
	struct my_dat *tl = (struct my_dat *)ptr;
	printk(KERN_INFO "I am in my timer func, jiffies = %ld\n", jiffies);
	printk(KERN_INFO "I think my current task pid is %d\n", (int)current->pid);
	printk(KERN_INFO "my data is: %d\n", tl->l);
	kfree(tl->tl);
	kfree(tl);
	atomic_dec(&ntimers);
	printk(KERN_INFO "ntimers deced to %d\n", atomic_read(&ntimers));
}

static ssize_t my_write(struct file *file, const char __user *buf, size_t lbuf, loff_t *ppos)
{
	struct timer_list *tl;
	struct my_dat *mdata;
	static int len = 100;
	atomic_inc(&ntimers);
	printk(KERN_INFO "ntimers upped to %d\n", atomic_read(&ntimers));
	tl = (struct timer_list *)kmalloc(sizeof(struct timer_list), GFP_KERNEL);
	printk(KERN_INFO "Entering the write function\n");
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
