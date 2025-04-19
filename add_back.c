#include "get_next_line.h"

t_entry	*ft_lstlast(t_entry *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	ft_lstadd_back(t_entry **lst, t_entry *new)
{
	t_entry	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	if (new && lst)
	{
		last = ft_lstlast(*lst);
		last -> next = new;
	}
}