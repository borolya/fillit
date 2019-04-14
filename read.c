#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "fillit.h"

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

void    ft_begin_lstadd(t_list **alst, t_list *new)
{
    t_list    *temp;

    if (!alst || !new)
        return ;
    if (*alst == NULL)
        *alst = new;
    else
    {
        temp = *alst;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = new;
    }
}

int read_file(int fd, int *count_elem_in_list, t_list **start)//1 ok, -1, ko//if(count == 0) - error
{
	char c;
	int res;
	char *str;
	char value;

	value = 'A';
	str = NULL;
	if (fd < 0 || !start)
	{
		return (-1);
	}
	while ((res = chech_tetr(fd, &str)) == 1)
	{
		(*count_elem_in_list)++;
		ft_begin_lstadd(start, ft_lstnew(get_piece(str, value++), sizeof(t_tetris)));
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
	return (-1);
}
