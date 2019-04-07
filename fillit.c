#include "libft.h"
//#include "filit.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_point
{
  int x;
  int y;
}   t_point;

t_point *point_new(int x, int y)
{
  t_point *point;

  point = ft_memalloc(sizeof(t_point));
  point->x = x;
  point->y = y;
  return (point);
}

typedef struct s_tetris
{
  char  **pos;
  int   width;
  int   height;
  char  value;
}   t_tetris;

t_tetris *new_tetra(char **pos, int width, int height, char value)
{
  t_tetris *tetra;

  tetra = ft_memalloc(sizeof(t_tetris));
  tetra->pos = pos;
  tetra->width = width;
  tetra->height = height;
  tetra->value = value;
  return (tetra);
}

t_list *ft_lstnew(void const *content, size_t content_size)
{
	t_list *elem;
	elem = (t_list*)ft_memalloc(sizeof(t_list));
	if (elem == NULL)
		return (NULL);
	if (content == NULL)
	{
		content_size = 0;
		elem->next = NULL;
	}
	else
	{
		elem->content = ft_memalloc(content_size);
		if (elem->content == NULL)
		{
			ft_memdel((void **)&elem);
			return (NULL);
		}
		ft_memcpy(elem->content, content, content_size);
	}
	elem->content_size = content_size;
	elem->next = NULL;
	return (elem);
}

void ft_lstadd(t_list **alst, t_list *new)
{
	new->next = *alst;
	*alst = new;
}


void ft_findminmax(char *str, t_point *min, t_point *max)
{
  int i;

  i = 0;
  while (i < 20)
  {
    if (str[i] == '#')
    {
      if (i / 5 < min->y)
        min->y = i / 5;
      if (i / 5 > max->y)
        max->y = i / 5;
      if (i % 5 < min->x)
        min->x = i % 5;
      if (i % 5 > max->x)
        max->x = i % 5;
    }
    i++;
  }
}

int   main()
{
  t_point   *min;
  t_point   *max;
  t_tetris  *tetra;
  char      **pos; // временно
  int       i;
  char      *str;
  char      value;
  t_list	*start;

  value = 'A';
  i = 0;
  str = "#...\n##..\n#...\n....\0";
  min = point_new(3,3);
  max = point_new(0,0);
  ft_findminmax(str, min, max);

  printf("max y = %d\n", max->y);
  printf("min y = %d\n", min->y);
  printf("max x = %d\n", max->x);
  printf("min x = %d\n", min->x);

  pos = ft_memalloc(sizeof(char**) * (max->y - min->y + 1));
  while (i < max->y - min->y + 1)
  {
    pos[i] = ft_strnew(max->x - min->x + 1);
    pos[i] = ft_strncpy(pos[i], str + min->x + (min->y + i) * 5, max->x - min->x + 1);
    i++;
  }
  tetra = new_tetra(pos, max->x - min->x + 1, max->y - min->y + 1, value);
  ft_memdel((void **)&min);
  ft_memdel((void **)&max);

  printf("Pos 0 = %s\n", pos[0]);
  printf("Pos 1 = %s\n", pos[1]);
  printf("Pos 2 = %s\n", pos[2]);

  ft_lstadd(&start, ft_lstnew(tetra, sizeof(t_tetris)));

  //printf("%s\n", f[0]);
  return (0);
}
