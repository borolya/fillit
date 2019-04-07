#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
# define ERROR ft_putstr("error\n"); exit(1);
typedef struct s_point
{
  int x;
  int y;
}   t_point;

typedef struct s_tetris
{
  char  **pos;
  int   width;
  int   height;
  char  value;
}   t_tetris;

typedef struct s_map
{
  int size;
  char **array;
} t_map;

#endif
