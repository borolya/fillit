#ifndef FILLIT_H
# define FILLIT_H

# include "libft.h"

# define ERROR ft_putstr("error\n"); exit(1);

typedef struct s_list
{
	void 			*content;
	size_t			content_size;
	struct	s_list	*next;
}				t_list;

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


t_tetris 	get_piece(char *str, char value);
void		ft_lstadd(t_list **alst, t_list *new);
t_list 		*ft_lstnew(void const *content, size_t content_size);

#endif
