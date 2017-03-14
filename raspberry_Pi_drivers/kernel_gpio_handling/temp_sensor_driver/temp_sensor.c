#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/workqueue.h>

#define READ_SCRATHPAD 0xBE

#define PIN 4
#define GPIO_NAME TEMP_PIN
#define WQ_NAME "work_queue"
#define WQ_HZ_DELAY HZ/10

static void work_handler(struct work_struct *work);

static struct workqueue_struct *led_wq;
static DECLARE_DELAYED_WORK(led_w, work_handler);

static void bus_pin_init(void)
{
	int ret;
	
	/* Initialization */
	ret = gpio_request(PIN, "GPIO_NAME");
	if (ret) {
		pr_err("request GPIO %d failed\n", PIN);
	}

	/* Setting GPIO function */
	ret = gpio_direction_input(PIN);
	if (ret) {
		pr_err("gpio_direction_input GPIO %d failed\n", PIN);
	}
}

static void master_reset(void)
{
	gpio_direction_output(PIN); 	/* pull the bus low */
	mdelay(480);
	gpio_direction_input(PIN);	/* release the bus */
	mdelay(60); 			/* wait for the maximum DS18B20 reaction time */

	if (gpio_get_value(PIN)) {
		pr_info("DS18B20 reset successful\n");
		return;
	}
	else {
		pr_info("DS18B20 NOT reset, try again in 1 second\n");
		sleep(1000);		/* wait for the maximum DS18B20 signal time before retry reset */
		master_reset();		/* try again */
	}
}

/*
static uint_8 read_bit(void)
{
	
}	

static void work_handler(struct work_struct *work)
{

}
*/

static int __init my_init(void)
{
	int ret;
	pr_info("Module Raspberry Pi\n");
	
	bus_pin_init();

	/*
	led_wq = create_singlethread_workqueue(WQ_NAME);
	if (led_wq) {
		pr_info("WQ created\n");
	} else {
		pr_err("No workqueue created\n");
	}

	ret = queue_delayed_work(led_wq, &led_w, WQ_HZ_DELAY);
	*/
	return 0;
}

static void __exit my_exit(void)
{
	pr_info("Goodbye, Module Raspberry Pi\n");

	gpio_free(PIN);
	/*
	cancel_delayed_work_sync(&led_w);
	destroy_workqueue(led_wq);
	*/
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ivan Slaev");
