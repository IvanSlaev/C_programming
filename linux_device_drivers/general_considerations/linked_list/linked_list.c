#include <linux/module.h>
#include <asm/atomic.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/init.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static LIST_HEAD(dog_list);

struct dogs
{
	struct list_head clist;
	int gate;
	char name[20];
};

static int __init my_init(void)
{
	struct dogs *doggy;
	int i;

	for (i = 0; i < 5; i++) 
	{
		if (!(doggy = kmalloc(sizeof(struct dogs), GFP_KERNEL))) 
		{
			printk(KERN_INFO "%s%d\n", "Failed to allocate memory for doggy: ", i);
			return -ENOMEM;
		}

		doggy->gate = 11 + i;
		sprintf(doggy->name, "Dog_%d", i + 1);
		printk(KERN_INFO "Adding %s at gate %d to list\n", doggy->name, doggy->gate);
		list_add(&doggy->clist, &dog_list);
	}
	return 0;
}

static void __exit my_exit(void)
{
	struct list_head *list;
	struct list_head *tmp;

	if (list_empty(&dog_list)) 
	{
		printk(KERN_INFO "%s\n", "Empty dog list");
		return;
	}
	printk(KERN_INFO "%s\n", "Camel list is not empty");

	list_for_each_safe(list, tmp, &dog_list)
	{
		struct dogs *doggy = list_entry(list, struct dogs, clist);
		list_del(&doggy->clist);
		printk(KERN_INFO "Dog %s at gate %d removed from list\n", doggy->name, doggy->gate);
		kfree(doggy);
	}

	if (list_empty(&dog_list)) 
	{
		printk(KERN_INFO "%s\n", "Empty list");
	}
	else
	{
		printk(KERN_INFO "%s\n", "List NOT empty");
	}
}

module_init(my_init);
module_exit(my_exit);
