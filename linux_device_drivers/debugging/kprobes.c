#include <linux/module.h>
#include <linux/init.h>
#include <linux/kprobes.h>
#include <linux/kallsyms.h>

#define PRCUT(t) printk(KERN_INFO "current->comm=%s, current->%s\n", t->comm, t->pid);

static char *name = "do_fork";
module_param(name, charp, S_IRUGO);

static struct kprobe kp;

static int my_pre_handler(struct kprobe *p, struct pt_regs *regs)
{
	printk(KERN_INFO "pre-handler: p->addr=0x%p\n", p->addr);
	return 0;
}

static void my_post_handler(struct kprobe *p, struct pt_regs *regs, unsigned long flags)
{
	printk(KERN_INFO "post_handler p->addr=0x%p\n", p->addr);
}

static int my_fault_handler(struct kprobe *p, struct pt_regs *regs, int trapnr)
{
	printk(KERN_INFO "fault_handler:p->addr=0x%p\n", p->addr);
	return 0;
}

static int __init my_init(void)
{
	kp.pre_handler = my_pre_handler;
	kp.post_handler = my_post_handler;
	kp.fault_handler = my_fault_handler;
	kp.symbol_name = name;

	if (register_kprobe(&kp)) 
	{
		printk(KERN_INFO "Failed to register kprobe\n");
		return -1;
	}

	printk(KERN_INFO "Kprobe module loaded at 0x%p\n", my_init);
	return 0;
}

static void __exit my_exit(void)
{
	unregister_kprobe(&kp);
	printk(KERN_INFO "Kprobe module unloaded at 0x%p\n", my_exit);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
