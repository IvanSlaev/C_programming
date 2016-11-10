TARGETS := $(wildcard *.c)

all:
	for TARGET in $(TARGETS); do \
		`obj-m = hello.o`; \
		$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules; \
         done
clean:
	for TARGET in $(TARGETS); do \
		$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean; \
         done
