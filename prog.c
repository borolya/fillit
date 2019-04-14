#include "fillit.h"

void print_map(t_map *map)
{
  int i;

  i = 0;
  while (i < map->size)
  {
    ft_putstr((map->array)[i]);
    ft_putchar('\n');
    i++;
  }
}

int check_capacity(t_map *map, t_tetris *tetr, int p, int q)
{
  int i;
  int j;

  i = 0;
  while (i < tetr->height)
  {
    j = 0;
    while (j < tetr->width)
    {
      if (tetr->pos[i][j] == '#' && (map->array)[p + i][q + j] != '.')
        return (0);
      j++;
    }
    i++;
  }
  return (1);
}

void change_map(t_map *map, t_tetris *tetr, int p, int q, char c)
{
  int i;
  int j;

  i = 0;
  while (i < tetr->height)
  {
    j = 0;
    while (j < tetr->width)
    {
        if (tetr->pos[i][j] == '#')
          (map->array)[p + i][q + j] = c;
        j++;
    }
    i++;
  }
}

int solve(t_map *map, t_list *list)
{
  int i;
  int j;
  t_tetris *tetr;

  if (list == NULL)
    return (1);
  tetr = list->content;
  i = 0;
  while (i + tetr->height <= map->size)
  {
    j = 0;
    while (j + tetr->width <= map->size)
    {
      if (check_capacity(map, tetr, i, j) == 1)
      {
          change_map(map, tetr, i, j, tetr->value);
        //  print_map(map);
         // ft_putstr("\n");
          if (solve(map, list->next) == 0)
          {
            change_map(map, tetr, i, j, '.');
         // print_map(map);
          //ft_putstr("\n");
          }
          else
            return (1);
      }
      j++;
    }
    i++;
  }
  return (0);
}


int sqrt_top(int nb)
{
	int sqrt;

	sqrt = 0;
	while (sqrt * sqrt < nb)
		sqrt++;
	return (sqrt);
}


t_map *new_map(int size)//if return NULL?  //if size <= 0 ?
{
  t_map *map;
  int i;
  int j;

  if (!(map = (t_map*)malloc(sizeof(t_map))))
    return (NULL);
  if(!(map->array = (char**)ft_memalloc(sizeof(char*) * size + 1)))
    return (NULL);
  i  = -1;
  while (++i < size)
  {
    if (!(map->array[i] = ft_strnew(size + 1)))
      return (NULL);
      j = -1;
      while (++j < size)
        map->array[i][j] = '.';
  }
  map->size = size;
  return (map);
}

/*
void del_tetra(void *tetra, size_t tetra_size)//tetra_size
{
  int i;

  i = 0;
  while (i < (t_tetris*)tetra->height)
  {
    free((t_tetris*)tetra->pos[i]);
    i++;
  }
  free((t_tetris*)tetra->pos);
  free(t_tetris*)(tetra);
  //?tetra_size = 0;
}
*/

void free_lst(t_list *alst)
{
  int i;
  t_tetris *tetr;
  t_list *tmp;

  while(alst)
  {
    tetr = (t_tetris*)alst->content;
    i = 0;
    while(i < tetr->height)
    {
      free(tetr->pos[i]);
      i++;
    }
    free(tetr->pos);
    free(tetr);
    tmp = alst->next;
    free(alst);
    alst = tmp;
  }
}

void free_map(t_map *map)
{
  int i;

  i = -1;
  while(++i < map->size)
    free(map->array[i]);
  free(map->array);
}

int main(int ac, char **av)
{
  t_map *map;
  t_list *start;
  int fd;
  int size;
  int count;
  int i;
  t_tetris *tetra;

  count = 0;
  start = NULL;
 // printf("ac = %d", ac);
  if (ac != 2)
  {
    ft_putstr("error\n");
    return (0);
  }
  fd = open(av[1], O_RDONLY);
  if (read_file(fd, &count, &start) != 1)
  {
    ft_putstr("error\n");
   // free_lst(start);
    exit(1);
  }
  size = sqrt_top(count * 4); //who we will find count?
  map = new_map(size);
  while (!solve(map, start))
  {
    free_map(map);
    map = new_map(size++);
  }
  print_map(map);
  //free_lst(start);
  //free_map(map);
  close(fd);
  return (0);
}
