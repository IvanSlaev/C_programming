#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#define PATH "./libs/lib_dll.so"

int main(void)
{

	char *err;
	void *handle;
	void (*print)(void);

	handle = dlopen (PATH, RTLD_LAZY);
	err = dlerror ();

	if (err)
	{
		printf("error");
	}

	print = dlsym (handle, "hello_dl");

	print(void);

	dlclose(handle);

	return 0;
}
