#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define DEF_DIR "."
#define DEATH(mess) { perror(mess); exit(errno); }

void process_dir(char *this_dir);

int main (int argc, char *argv[])
{
	char *dirname = DEF_DIR;
	if (argc > 1)
	{
		dirname = argv[1];
	}
	printf("Dir: %s , PID: %d\n", dirname, getpid());
	process_dir(dirname);
	exit(EXIT_SUCCESS);
}

void process_dir(char *this_dir)
{
	DIR *dir;
	struct dirent *direntry;
	struct stat file_info;
	int status;
	
	if (chdir(this_dir))
	{
		DEATH(this_dir);
	}
	if (!(dir = opendir("./")))
	{
		DEATH(this_dir);
	}
	
	/*List all dir entries*/
	
	while ((direntry = readdir(dir)))
	{
		if (lstat(direntry->d_name, &file_info))
		{
			fprintf(stderr, "Error lstat()ing %s\n", direntry->d_name);
		}
		printf("	%d:   %s\n", getpid(), direntry->d_name);
	}
	
	rewinddir(dir);
	
	while ((direntry = readdir(dir)))
	{
		if (lstat(direntry->d_name, &file_info))
		{
			fprintf(stderr, "Error lstat()ing %s\n", direntry->d_name);
		}
		else if (S_ISDIR(file_info.st_mode))
		{
			pid_t pid;
			
			if (strcmp(direntry->d_name, ".") && strcmp(direntry->d_name, ".."))
			{
				/*fflush(stdout);*/
				pid = fork();
				if (pid == 0)
				{
					printf("\nPID %d DIRECTORY: %s\n", getpid(), direntry->d_name);
					process_dir(direntry->d_name);
					exit(EXIT_SUCCESS);
				}
				if (pid > 0)
				{
					wait(&status);
				}
				else
				{
					DEATH("fork failed");
				}
			}
		}
	}
	closedir(dir);
}
