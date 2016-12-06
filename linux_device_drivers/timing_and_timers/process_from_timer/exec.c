#include <linux/module.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <asm/msr.h>
#include <linux/jiffies.h>
#include <linux/slab.h>

static char *str; // string to pass to module
module_param(str, charp, S_IRUGO);

static unsigned long speed; //MHZ of CPU
static struct timer_list timer_a, timer_b;

static struct kt_data {
	unsigned long period;
	unsigned long start_time; // jiffies value when first start the timer
	u64 tsc_start; // TSC when timer was queued
	u64 tsc_end; // TSC when timer is executed
}*data_a, *data_b;

static void ktfun_a(unsigned long var)
{
	u64 ticks;
	int msecs;
	struct kt_data *tdata = (struct kt_data *)var;

	rdtscll(tdata->tsc_end);
	ticks = tdata->tsc_end - tdata->tsc_start;
	msecs = (unsigned long)ticks / (speed * 1000);
	printk(KERN_INFO "A: period = %ld, elapsed = %ld, TSC ticks = %lld, msecs = %d\n", tdata->period, jiffies - tdata->start_time, ticks, msecs);
	rdtscll(tdata->tsc_start);
	mod_timer(&timer_a, tdata->period + jiffies);
}

static void ktfun_b(unsigned long var)
{
	int rc;
	char *argv[] = { "wall", "This is a message from the Kernel", NULL };
	static char *envp[] = { NULL };
	struct kt_data *tdata = (struct kt_data *)var;
	printk(KERN_INFO "B: period = %ld, elapsed = %ld\n", tdata->period, jiffies - tdata->start_time);
	if (str) 
	{
		argv[1] = str;
	}
	printk(KERN_INFO "Trying to execute %s %s\n", argv[0], argv[1]);
	rc = call_usermodehelper("/usr/bin/wall", argv, envp, 0);
	if (rc) 
	{
		printk(KERN_INFO "Failed to execute %s %s\n", argv[0], argv[1]);
	}
	// resubmit
	mod_timer(&timer_b, tdata->period + jiffies);
}

static int __init my_init(void)
{
	speed = cpu_khz / 1000;
	printk(KERN_INFO "CPU MHZ is found to be: %ld\n", speed);

	init_timer(&timer_a);
	init_timer(&timer_b);

	timer_a.function = ktfun_a;
	timer_b.function = ktfun_b;

	data_a = kmalloc(sizeof(*data_a), GFP_KERNEL);
	data_b = kmalloc(sizeof(*data_b), GFP_KERNEL);

	timer_a.data = (unsigned long)data_a;
	timer_b.data = (unsigned long)data_b;

	data_a->period = 1 * HZ; //1 sec.
	data_b->period = 10 * HZ; //10 secs

	data_a->start_time = jiffies;
	data_b->start_time = jiffies;

	timer_a.expires = jiffies + data_a->period;
	timer_b.expires = jiffies + data_b->period;

	rdtscll(data_a->tsc_start);

	add_timer(&timer_a);
	add_timer(&timer_b);

	return 0;
}

static void __exit my_exit(void)
{
	// delete any running timers
	printk(KERN_INFO "Delete timer A: rc = %d\n", del_timer_sync(&timer_a));
	printk(KERN_INFO "Delete timer B: rc = %d\n", del_timer_sync(&timer_b));
	kfree(data_a);
	kfree(data_b);
	printk(KERN_INFO "Module successfully unloaded\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
