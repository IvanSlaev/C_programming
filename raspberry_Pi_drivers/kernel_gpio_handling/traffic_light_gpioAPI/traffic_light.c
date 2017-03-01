#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

#define RED 17
#define BUTTON 18
#define GREEN 27
#define WQ_NAME "led_work_queue"
#define WQ_HZ_DELAY HZ/10
/*
static struct gpio red_led_struct;
static struct gpio green_led_struct;
static struct gpio button_struct;
*/
static void work_handler(struct work_struct *work);

static struct workqueue_struct *led_wq;
static DECLARE_DELAYED_WORK(led_w, work_handler);

static void work_handler(struct work_struct *work)
{
	int ret;

	while (1) {
		ret = gpio_get_value(BUTTON);
		if (ret) {
			gpio_set_value(RED, 1);
			msleep(1000);
			gpio_set_value(RED, 0);
			msleep(500);
			gpio_set_value(GREEN, 1);
			msleep(1000);
			gpio_set_value(GREEN, 0);
			break;
		}
	}
}
 
static int __init my_init(void)
{
	int ret;
	pr_info("Module Raspberry Pi\n");

	/* Initialization */
	ret = gpio_request(RED, "RED_LED");
	if (ret) {
		pr_err("request GPIO %d failed\n", RED);
	}
	ret = gpio_request(BUTTON, "BUTTON");
	if (ret) {
		pr_err("request GPIO %d failed\n", BUTTON);
	}
	ret = gpio_request(GREEN, "GREEN_LED");
	if (ret) {
		pr_err("request GPIO %d failed\n", GREEN);
	}

	/* Setting GPIO function */
	ret = gpio_direction_output(RED, 0);
	if (ret) {
		pr_err("gpio_direction_output GPIO %d failed\n", RED);
	}
	ret = gpio_direction_input(BUTTON);
	if (ret) {
		pr_err("gpio_direction_input GPIO %d failed\n", BUTTON);
	}
	ret = gpio_direction_output(GREEN, 0);
	if (ret) {
		pr_err("gpio_direction_output GPIO %d failed\n", GREEN);
	}

	led_wq = create_singlethread_workqueue(WQ_NAME);
	if (led_wq) {
		pr_info("WQ created\n");
		ret = queue_delayed_work(led_wq, &led_w, WQ_HZ_DELAY);
		if (!ret) {
			pr_err("work initialization failed\n");
		}
	} else {
		pr_err("No workqueue created\n");
	}

	return 0;
}

static void __exit my_exit(void)
{
	pr_info("before free red\n");
	gpio_free(RED);
	pr_info("before free button\n");
	gpio_free(BUTTON);
	pr_info("before free green\n");
	gpio_free(GREEN);
	pr_info("before work delay cancel\n");

	cancel_delayed_work_sync(&led_w);
	pr_info("before workq destroy\n");

	destroy_workqueue(led_wq);

	printk(KERN_INFO "Goodbye, Module Raspberry P\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Slaev");
