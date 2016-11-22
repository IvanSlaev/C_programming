#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

#define DEATH(mess) { perror(mess); exit(errno); }
#define SHARED_IRQ 16

static int irq = SHARED_IRQ, my_dev_id, irq_counter;
module_param(irq, int, S_IRUGO);

static irqreturn_t my_interrupt(int irq, void *dev_id)
{
	irq_counter++;
	printk(KERN_INFO "In the ISR: counter = %d\n", irq_counter);
	return IRQ_NONE;
}

static int __init my_init(void)
{
	if (request_irq(irq, my_interrupt, IRQF_SHARED, "my_interrupt", &my_dev_id)) 
	{
		return -1;
	}
	printk(KERN_INFO "Successfully loaded ISR handler\n");
	return 0;
}

static void __exit my_exit(void)
{
	synchronize_irq(irq);
	free_irq(irq, &my_dev_id);
	printk(KERN_INFO "Successfully unloading, irq requests: %d\n", irq_counter);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");