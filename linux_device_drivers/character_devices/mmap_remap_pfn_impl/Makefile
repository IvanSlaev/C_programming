obj-m += remap_pfn.o
TEST_SRC=${wildcard ./testit/*.c}

all: test
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean: clean_test
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test: $(TEST_SRC)
	$(CC) -o $@ $^
clean_test:
	rm test
