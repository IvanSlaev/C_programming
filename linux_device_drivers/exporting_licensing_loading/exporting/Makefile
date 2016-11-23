obj-m = module_1.o module_2.o 

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
install:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules_install
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
