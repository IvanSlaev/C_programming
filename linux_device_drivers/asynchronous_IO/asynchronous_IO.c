#include "chardev_macro.h"
#include <linux/module.h>
#include <linux/aio.h>

static ssize_t mycdrv_aio_read(struct kiocb *iocb, const struct iovec *iov, unsigned long niov, loff_t offset)
{
	printk(KERN_INFO "Entering mycdrv_aio_read\n");
	return mycdrv_generic_read(iocb->ki_filp, iov->iov_base, iov->iov_len, &offset);
}

static ssize_t mycdrv_aio_write(struct kiocb *iocb, const struct iovec *iov, unsigned long niov, loff_t offset)
{
	printk(KERN_INFO "Entering mycdrv_aio_write\n");
	return mycdrv_generic_write(iocb->ki_filp, iov->iov_base, iov->iov_len, &offset);
}

static const struct file_operations mycdrv_fops = {
	.owner = THIS_MODULE,
	.read = mycdrv_generic_read,
	.write = mycdrv_generic_write,
	.open = mycdrv_generic_open,
	.release = mycdrv_generic_release,
	.llseek = mycdrv_generic_lseek,
	.aio_read = mycdrv_aio_read,
	.aio_write = mycdrv_aio_write
};

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
