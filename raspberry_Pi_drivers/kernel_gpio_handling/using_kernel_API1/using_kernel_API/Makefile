obj-m := gpio_API.o

KDIR := ~/linux
PWD := $(shell pwd)

default:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) clean
