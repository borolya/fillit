
#include <unistd.h>
#include <stdio.h>

int link_count(char buff[], int i)
{
	int link;
	
	//printf("i = %d\n", i);
	link = 0;
	if (i % 5 != 0 && buff[i - 1] == '#')
		link++;
	if (i % 5 != 3 && buff[i + 1] == '#')
		link++;
	if (i / 5 != 0 && buff[i - 5] == '#')
		link++;
	if (i / 5 != 3 && buff[i + 5] == '#')
		link++;
	//printf("link = %d\n", link);
	return (link);
}

int chech_tetr(int fd) //-1 error, 0 not read, 1 ok
{
	char buff[19];
	int res;
	int count;
	int link;
	int i;

	res = read(fd, buff, 19);
	//printf("buff = |%s|\n", buff);
	if (res == 0)
		return (0);
	if (res < 19)
		return (-1);
	if (buff[4] != '\n' || buff[9] != '\n' || buff[14] != '\n')
		return (-1);
	i = 0;
	count = 0;
	link = 0;
	while (i < 19)
	{
		if(buff[i] == '#' && i % 5 != 4)
		{
			count++;
			link = link + link_count(buff, i);
		}
		else if (buff[i] != '.' && i % 5 != 4)
			return (-1);
		if (count > 4)
			return (-1);
		i++;
	}
	if (link != 6 && link != 8)
		return (-1);
	return (1);
}


int check_correct(int fd)//1 ok, -1, ko
{
	char c;
	int res;
	
	if (fd < 0)
		return (-1);
	if (chech_tetr(fd) < 1)
		return (-1);
	res = read(fd, &c, 1);
	if ((res == 1 && c != '\n') || res < 0)
		return (-1);
	else if (res == 0)
		return (1);
	res = read(fd, &c, 1);
	if ((res == 1 && c != '\n') || res < 0)
		return (-1);
	else if (res == 0)
		return (1);
	while (chech_tetr(fd) == 1)
	{
		res = read(fd, &c, 1);
		if ((res == 1 && c != '\n') || res < 0)
			return (-1);
		else if (res == 0)
			return (1);
		res = read(fd, &c, 1);
		if ((res == 1 && c != '\n') || res < 0)
			return (-1);
		else if (res == 0)
			return (1);
	}
	if (chech_tetr(fd) == 0)
		return (1);	
	return (-1);
}
