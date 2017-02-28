obj-m := gpio_API.o

CROSS_COMP := ARCH=arm CROSS_COMPILE=/home/users/islaev/raspberrypi/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin/arm-linux-gnueabihf-
KDIR := ~/raspberrypi/linux
PWD := $(shell pwd)

default:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) $(CROSS_COMP) -C $(KDIR) SUBDIRS=$(PWD) clean
