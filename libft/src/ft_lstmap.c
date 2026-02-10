/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:47:41 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/*
void	*ft_strtouppper(void	*content)
{
	if(!content)
		EXIT_FAILURE;

	*(unsigned char *)content -= 32;
	return	content;
}

void	ft_putlst(t_list	*lst)
{
	t_list	*current = NULL;
	current = lst;

	while (current)
	{
		printf("%s->",(char*)current->content);
		current = current->next;
	}
	printf("NULL");
}

void	ft_putaddress(t_list	*lst)
{
	t_list	*current = NULL;
	current = lst;

	while (current)
	{
		printf("%p->",current->content);
		current = current->next;
	}
	printf("NULL");
}
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newnode;
	t_list	*newcontent;
	t_list	*currentcpy;

	currentcpy = lst;
	newlst = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (currentcpy)
	{
		newcontent = (f(currentcpy->content));
		newnode = ft_lstnew(newcontent);
		if (!newnode)
		{
			del(newcontent);
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newnode);
		currentcpy = currentcpy->next;
	}
	return (newlst);
}
/*
int main()
{
	t_list *new = NULL;
	t_list	*lst = NULL;

	ft_lstadd_front(&lst,ft_lstnew(ft_strdup("a")));
	ft_lstadd_front(&lst,ft_lstnew(ft_strdup("b")));
	ft_lstadd_front(&lst,ft_lstnew(ft_strdup("c")));

	write(1, "lst =", 5);
	ft_putlst(lst);
	printf("\n");

	write(1, "lst =", 5);
	ft_putaddress(lst);
	printf("\n");


	new = ft_lstmap(lst,ft_strtouppper,free);

	write(1, "new =", 5);
	ft_putlst(new);
	printf("\n");

	write(1, "new =", 5);
	ft_putaddress(new);
	printf("\n");

	ft_lstclear(&lst,free);
	ft_lstclear(&new,free);
	printf("%p\n",lst);
	printf("%p\n",new);
}
*/
