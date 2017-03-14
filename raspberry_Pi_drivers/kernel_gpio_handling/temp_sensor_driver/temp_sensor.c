#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/workqueue.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>

#define RED 17
#define BUTTON 18
#define GREEN 27
#define WQ_NAME "led_work_queue"
#define WQ_HZ_DELAY HZ/10

static int irq;

static void work_handler(struct work_struct *work);

static struct workqueue_struct *led_wq;
static DECLARE_DELAYED_WORK(led_w, work_handler);

static void work_handler(struct work_struct *work)
{
	pr_info("Button working\n");
}
 
static irqreturn_t irq_handler_gpio(int irq, void *dev_id)
{
	int ret;

	disable_irq_nosync(irq);
	ret = queue_delayed_work(led_wq, &led_w, WQ_HZ_DELAY);

	return IRQ_HANDLED;
}

static int __init my_init(void)
{
	int ret;
	pr_info("Module Raspberry Pi\n");
	
	/* Initialization */
	ret = gpio_request(BUTTON, "BUTTON");
	if (ret) {
		pr_err("request GPIO %d failed\n", BUTTON);
	}

	/* Setting GPIO function */

	ret = gpio_direction_input(BUTTON);
	if (ret) {
		pr_err("gpio_direction_input GPIO %d failed\n", BUTTON);
	}

	irq = gpio_to_irq(BUTTON);
	if (!irq) {
		pr_err("gpio_to_irq failed \n");
	}	
	
	led_wq = create_singlethread_workqueue(WQ_NAME);
	if (led_wq) {
		pr_info("WQ created\n");
	} else {
		pr_err("No workqueue created\n");
	}

	ret = request_irq(irq, irq_handler_gpio, IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "button", NULL);
	if (ret) {
		pr_err("irq request failed\n");
	}

	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Goodbye, Module Raspberry Pi\n");

	gpio_free(BUTTON);

	cancel_delayed_work_sync(&led_w);

	destroy_workqueue(led_wq);
	free_irq(irq, NULL);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Slaev");
