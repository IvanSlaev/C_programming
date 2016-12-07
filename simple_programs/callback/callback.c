#include <stdio.h>
#include <stdlib.h>

void calling_function(int (*callback_function)()) {
	printf("sum: %d\n", callback_function() + callback_function());
}

int first_callback()
{
	return 5000;
}

int second_callback()
{
	return 2500;
}

int main()
{
	// You can call it as you wish, because
	// my_func(...) == my_func == &my_func(...) == &my_func when no argumets to callback functions
	calling_function(&first_callback);
	calling_function(first_callback);
	
	// same for any other function taking no arguments and returning int (in this example)
	calling_function(&second_callback);
	calling_function(second_callback);
	return 0;
}
