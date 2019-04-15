#include "fillit.h"

void free_tetra(t_tetris **tetr)
{
  int i;

  i = 0;
  while(i < (*tetr)->height)
  {
    free((*tetr)->pos[i]);
    i++;
  }
  free((*tetr)->pos);
  free(*tetr);
}

void free_lst(t_list **alst)
{
  t_list *tmp;

  while(*alst)
  {
    free_tetra((t_tetris**)&((*alst)->content));
    tmp = (*alst)->next;
  //  free((*alst)->content);
    free(*alst);
    *alst = tmp;
  }
}

void free_map(t_map **map)
{
  int i;

  i = -1;
  while(++i < (*map)->size)
    free((*map)->array[i]);
  free(((*map)->array));
  free(*map);
}