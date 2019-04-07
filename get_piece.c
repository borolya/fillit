#include "libft.h"
#include "fillit.h"

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

t_point *point_new(int x, int y)
{
  t_point *point;

  point = ft_memalloc(sizeof(t_point));
  point->x = x;
  point->y = y;
  return (point);
}

t_tetris *get_piece(char *str, char value)
{
	t_tetris  *tetra;
	t_point   *min;
    t_point   *max;
	char      **pos;
	int       i;

	min = point_new(3,3);
    max = point_new(0,0);
    ft_findminmax(str, min, max);

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
	return (tetra);
}
