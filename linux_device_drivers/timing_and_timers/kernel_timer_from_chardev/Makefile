obj-m += timer.o

all: test
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test: test.c
	$(CC) -o $@ $^
