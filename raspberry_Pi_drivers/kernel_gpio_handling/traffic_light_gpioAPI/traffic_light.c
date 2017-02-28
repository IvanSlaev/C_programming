#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define RED 17
#define BUTTON 18
#define GREEN 27

static int __init params_init(void)
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
		}
	}
	return 0;
}

static void __exit params_exit(void)
{
	gpio_set_value(RED, 0);
	gpio_set_value(GREEN, 0);

	gpio_free(RED);
	gpio_free(BUTTON);
	gpio_free(GREEN);
	printk(KERN_INFO "Goodbye, Module Raspberry P\n");
}

module_init(params_init);
module_exit(params_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Slaev");
