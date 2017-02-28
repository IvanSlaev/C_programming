obj-m := gpio_API.o

CROSS_COMP := ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-
KDIR := ~/raspberrypi/linux
PWD := $(shell pwd)

default:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) clean
