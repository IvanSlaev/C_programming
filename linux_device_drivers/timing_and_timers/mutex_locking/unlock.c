#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>

static DEFINE_MUTEX (my_mutex);
static struct timer_list timr;

static void ktfun(unsigned long var)
{
	printk(KERN_INFO "timer executing at jiffies = %ld\n", jiffies);
	mutex_lock(&my_mutex);
	printk(KERN_INFO "Init mutex in locked state, count = %d\n", atomic_read(&my_mutex.count));
	mutex_unlock(&my_mutex);
	printk(KERN_INFO "mutex unlocked in timer, count = %d\n", atomic_read(&my_mutex.count));
}

static int __init my_init(void)
{
	init_timer(&timr);
	timr.expires = jiffies + 3 * HZ;  //3 sec.
	timr.function = ktfun;
	add_timer(&timr);
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "Delete timer A: rc = %d\n", del_timer_sync(&timr));
	printk(KERN_INFO "Exiting with mutex having count = %d\n", atomic_read(&my_mutex.count));
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
