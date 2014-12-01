#include <dirent.h> 
#include <stdio.h>
#include <sys/stat.h>
#include "my_types.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dtermin()

int determine_dir(char direct[])
{
	struct stat status;

	stat(direct, &status);

	if (status.st_mode & S_IFDIR) // is a directory file.
		return 0;
	if (status.st_mode & S_IFREG) // is a regular file.
		return 1;
}


void fd_generator(char *direct, int *index)
{
	int regular = 0;
	int count, i;
	char *abs_dir;
	DIR *d;
	struct dirent *dir;

	d = opendir(direct);

	if (d != NULL)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
			{	
				for(i = 0; dir->d_name[i] != '\0'; i++)
					count++;
				abs_dir = (char*)malloc((count + 2) * sizeof(char));
				strcpy(abs_dir, direct);
				strcat(abs_dir, "/");
				strcat(abs_dir, dir->d_name);

				pool->fd_pool[*index] = open(abs_dir, O_RDONLY);
				(*index)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
					fd_generator(abs_dir, index);
			}
		}
	}
}
