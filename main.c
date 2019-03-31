#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int check_correct(int fd);

int main(void)
{
  int fd;

  fd = open("test.txt", O_RDONLY);
  printf("%d\n", check_correct(fd));
	return (0);
}
