#include <dirent.h> 
#include <stdio.h>
#include <sys/stat.h>
#include "my_types.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int determine_num()
{

}

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
				abs_dir = strcat(direct, "/");
				abs_dir = strcat(abs_dir, dir->d_name);

				pool->fd_pool[*index] = open(abs_dir, O_RDONLY);
				(*index)++;

				regular = determine_dir(abs_dir);

				if (regular == 0)
					fd_generator(abs_dir, index);
			}
		}
	}
}
