#include <unistd.h>
#include <stdio.h>
#include "libft.h"

int link_count(char buff[], int i)
{
	int link;

	link = 0;
	if (i % 5 != 0 && buff[i - 1] == '#')
		link++;
	if (i % 5 != 3 && buff[i + 1] == '#')
		link++;
	if (i / 5 != 0 && buff[i - 5] == '#')
		link++;
	if (i / 5 != 3 && buff[i + 5] == '#')
		link++;
	return (link);
}

int chech_tetr(int fd, char **str) //-1 error, 0 not read, 1 ok and pake str
{
	char buff[20];
	int res;
	int count;
	int link;
	int i;

	res = read(fd, buff, 19);
	buff[19] = '\0';
	//printf("buff = |%s|\n", buff);
	if (res == 0)
		return (0);
	else if (res < 19)
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
	*str = ft_strdup(buff); //if NULL !?
	return (1);
}

/*
	we can add this function in libft
*/
int count_elem_in_list(t_list *start)
{
	int i;

	i = 0;
	while (start)
	{
		start = start->next;
		i++;
	}
	return (i);
}

t_list *read_file(int fd, int *count_elem_in_list, t_list **start)//1 ok, -1, ko//if(count == 0) - error
{
	char c;
	int res;
	char *str;
	char value;
	t_tetris  *tetra;

	value = 'A';
	str = NULL;
	if (fd < 0 || !start)
		return (-1);
	while (chech_tetr(fd, &str))
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
		tetra = get_piece(str, value);
		ft_lstadd(&start, ft_lstnew(tetra, sizeof(t_tetris)));
		printf("%s\n", str);
	}
	*count_elem_in_list = count_elem_in_list(start);
	if (res == 0 && count_elem_in_list > 0)
		return (start);

	//free_lst(start);
	return (-1);
}
