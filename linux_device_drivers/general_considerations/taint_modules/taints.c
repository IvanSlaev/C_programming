#include <linux/module.h>
#include <linux/init.h>

#define DEATH(mess) { perror(mess); exit(errno); }

static int __init my_init(void)
{
	int j = 0;
	struct list_head *modules;
	struct module *m = THIS_MODULE;
	modules = &m->list;
	printk(KERN_INFO "\n");
	printk(KERN_INFO "%3d MOD:%20s, teints = %d\n", j++, m->name, m->taints);
	list_for_each_entry(m, modules, list)
	{
		printk(KERN_INFO "%3d MOD:%20s, teints = %d\n", j++, m->name, m->taints);
		if (j > 50) 
		{
			break;
		}
		return 0;
	}
	return 0;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "BYE: module unloaded from 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);
