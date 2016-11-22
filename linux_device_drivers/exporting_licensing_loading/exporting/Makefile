obj-m = module_1.o module_2.o 

all:
		$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
		$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

get_interrupt: get_interrupt.c
	gcc $< -o $@
