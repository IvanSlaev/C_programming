#include <stdio.h>
#include <sys/ioctl.h>  

int kbhit()  
{ 
	 int i;  
	 ioctl(0, FIONREAD, &i);  
	 return i; /* return a count of chars available to read */  
}  

main()  
{ 
	int i = 0;  
	int c;  
	
	system("stty raw -echo");
	while (c!='q') {
	       i++;	
	       if (kbhit()) { 
			c = getchar();  
			printf("Got %c, on iteration %d\n",c, i);  
		}  
	     }  
	system("stty cooked echo");  
} 
