#include "libft.h"
#include "fillit.h"

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

void	ft_lstadd(t_list **alst, t_list *new)//in beginning
{
	new->next = *alst;
	*alst = new;
}
