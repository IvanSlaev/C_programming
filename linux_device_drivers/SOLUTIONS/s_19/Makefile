### Automatic Makefile generation by 'genmake' script        ####
### Copyright, Jerry Cooperstein, coop@linuxfoundation.org 2/2003 - 1/2012 ####
### License: GPLv2 ###

obj-m +=  lab1_complete.o lab1_excl.o lab1_semaphore.o lab1_semaphore_rw.o lab1_wait_event.o lab2_killable.o lab3_poll.o

export KROOT=/lib/modules/3.19.0-66-generic/build

export ARCH=x86

allofit:  userprogs modules
modules:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

userprogs:
	@$(MAKE) \
		CFLAGS="-O2 -Wall -pedantic" \
	 lab1_read lab1_write lab3_poll_test

clean: kernel_clean
	rm -rf  lab1_read lab1_write lab3_poll_test  Module.symvers modules.order
