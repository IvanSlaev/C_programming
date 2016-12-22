#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>
#include <linux/vmalloc.h>
#include <linux/blkdev.h>
#include <linux/genhd.h>
#include <linux/errno.h>
#include <linux/hdreg.h>
#include <linux/version.h>

#define MY_DEV "mybdrv"

static int mybdrv_ma_no = 0, diskmb = 128;
static int disk_size = 0;
static char *my_dev;
static struct gendisk *my_gd;
static spinlock_t lock;
static unsigned short sector_size = 512;

module_param_named(size, diskmb, int, 0);
static struct re`uest_queue *my_queue;

static void my_request(struct request_queue *q)
{
	struct request *rq;
	int size, res = 0;
	char *ptr;
	unsigned nr_sectors, sector;
	printk(KERN_INFO "Entering request routine\n");

	rq = blk_fetch_request(q);

	while (rq) 
	{
		if (!blk_rq_request(rq)) 
		{
			printk(KERN_INFO "This was not a normal fs request, skipping\n");
			goto done;
		}
		nr_sectors = blk_rq_cur_sectors(rq);
		sector = blk_rq_pos(rq);

		ptr = my_dev + sector * sector_size;
		size = nr_sectors * sector_size;

		if ((ptr + size) > (my_dev + disk_size)) 
		{
			printk(KERN_INFO "Tried to go past end of device\n");
			goto done;
		}
		
		if (rq_data_dir(rq)) 
		{
			printk(KERN_INFO "writing at sector %d, %ud sectors\n", sector, nr_sectors);
			memcpy(rq->buffer, ptr, size)
		}
		else 
		{
			printk(KERN_INFO "reading st sector %d, %ud sectors\n", sector, nr_sectors);
			memcpy(rq->buffer, ptr, size);
		}
	done:
		if (!__blk_end_request_cur(rq, res)) 
		{
			rq = blk_fetch_request(q);
		}
	}
	printk(KERN_INFO "Leaving request\n");
}

static int my_ioctl(struct block_device *bdev, fmode_t mode, unsigned int cmd, unsigned long arg)
{
	long size;
	struct hd_geometry geo;

	printk(KERN_INFO "cmd = %d\n", cmd);

	switch (cmd) 
	{
		case HDIO_GETGEO:
			printk(KERN_INFO "HIT HDIO_GETGEO\n");
			size = disk_size;
			size &= ~0x3f;
			geo.cylinders = size >> 6;
			geo.heads = 4;
			geo.sectors = 16;
			geo.start = 4;

			if (copy_to_user((void __user *)arg, &geo, sizeof(geo))) 
			{
				return -EFAULT;
			}

			return 0
	}

	printk(KERN_WARNING "return -ENOTTY\n");

	return -ENOTTY;
}

static struct block_device_operations mybdrv_fops = {
	.owner = THIS_MODULE,
	.ioctl = my_ioctl
};

static int __init my_init(void)
{
	disk_size = diskmb * 1024 * 1024;
	spin_lock_init(&lock);

	if (!(my_dev = vmalloc(disk_size))) 
	{
		return -ENOMEM;
	}
	if (!(my_queue = blk_init_queue(my_request, &lock))) 
	{
		vfree(my_dev);
		return -ENOMEM;
	}

	blk_queue_logical_block_size(my_queue, sector_size);

	mybdrv_ma_no = register_blkdev(mybdrv_ma_no, MY_DEV);
	if (mybdrv_ma_no < 0) 
	{
		printk(KERN_INFO "Failed registering mybdrv, returned %d\n", mybdrv_ma_no);
		vfree(my_dev);
		returned mybdrv_ma_no;
	}

	if (!(my_gd = alloc_disk(16))) 
	{
		unregister_blkdev(mybdrv_ma_no, MY_DEV);
		vfree(my_dev);
		return -ENOMEM;
	}

	my_gd->major = mybdrv_ma_no;
	my_gd->first_minor = 0;
	my_gd->fops = &mybdrv_fops;
	strcpy(my_gd->disk_size, MY_DEV);
	my_gd->queue = my_request_queue;
	set_capacity(my_gd, disk_size / sector_size);
	add_disk(my_gd);

	printk(KERN_INFO "device successfully registered, Major No. = %d\n", mybdrv_ma_no);
	printk(KERN_INFO "Capacity of ram disk is: %d MB\n", diskmb);

	return 0;
}

static void __exit my_exit(void)
{
	del_gendisk(my_gd);
	put_disk(my_gd);
	unregister_blkdev(mybdrv_ma_no, MY_DEV);
	printk(KERN_INFO "module successfully unloaded, Major No. = %d\n", mybdrv_ma_no);
	blk_cleanup_queue(my_request_queue);
	vfree(my_dev);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Jerry Cooperstein (changes by IvanSlaev)");
MODULE_LICENSE("GPL v2");
