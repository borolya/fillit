#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

int read_file(int fd);

int main(void)
{
  int fd;

  fd = open("test.txt", O_RDONLY);
  if (read_file(fd) == 1)
    printf("everythink ok!");
	return (0);
}
