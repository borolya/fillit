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

int chech_tetr(int res, char buf[]) //-1 error, 0 not read, 1 ok and pake str
{
	int count;
	int i;
	int link;

	i = 0;
	count = 0;
	link = 0;

	if (buf[4] != '\n' || buf[9] != '\n' || buf[14] != '\n' || buf[19] != '\n'
											|| buf[20] != '\n')
		return (-1);
	while (i < 20)
	{
		if(buf[i] == '#' && i % 5 != 4)
		{
			count++;
			link = link + link_count(buf, i);
		}
		else if (buf[i] != '.' && i % 5 != 4)
			return (-1);
		if (count > 4)
			return (-1);
		i++;
	}
	if (link != 6 && link != 8)
		return (-1);
	return (1);
}

/*
	we can add this function in libft
*/
/*
int count_elem(t_list *start)
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
*/
int read_file(int fd, int *tetra_count, t_list **start)//1 ok, -1, ko//if(count == 0) - error
{
	int res;
	char buf[22];
	char value;
		t_tetris  *tetra;
	int i; // потом удалить
	
	i = 0;
		value = 'A';
	if (fd < 0 || !start)
		return (-1);
		while ((res = read(fd, buf, 21)) >= 20)
	{
		buf[21] = '\0';
		if (chech_tetr(res, buf) == 1)
		{
			tetra_count++;
			printf("tetr = %d", *tetra_count);
			tetra =  get_piece(buf, value++); //
			while(i < tetra->height) // потом удалить это для проверки
			{
				printf("Tetra %d pos[%d] = %s \n", *tetra_count, i, tetra->pos[i]); //
				i++;
			}
		}
		else
		{
			ft_putstr("tyty");
			return(-1);
		}
		i = 0; // потом удалить
		ft_lstadd(start, ft_lstnew(tetra, sizeof(t_tetris)));
	}
	if (res == 0 && tetra_count > 0)
		return (1);

	//free_lst(start);
	return (-1);
}
