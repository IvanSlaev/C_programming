obj-m := gpio_API.o

CROSS_COMP := ARCH=arm CROSS_COMPILE=~/raspberrypi/tools/arm-bcm2708/arm-bcm2708-linux-gnueabi/bin/arm-bcm2708-linux-gnueabi-
KDIR := ~/raspberrypi/linux
PWD := $(shell pwd)

default:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) clean
