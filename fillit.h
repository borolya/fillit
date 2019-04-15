#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>

# define ERROR ft_putstr("error\n"); exit(1);
/*
typedef struct s_list
{
	void 			*content;
	size_t			content_size;
	struct	s_list	*next;
}				t_list;
*/
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

void free_tetra(t_tetris **tetr);
void free_lst(t_list **alst);
void free_map(t_map **map);
t_tetris 	*get_piece(char *str, char value);
int read_file(int fd, int *count_elem_in_list, t_list **start);
//void		ft_lstadd(t_list **alst, t_list *new);
//t_list 		*ft_lstnew(void const *content, size_t content_size);

#endif
