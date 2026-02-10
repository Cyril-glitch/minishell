/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:42:42 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/*
void	ft_putlst(t_list	*lst)
{
	t_list	*current = NULL;
	current = lst;

	while(current)
	{
		printf("%s",(char*)current->content);
		current = current->next;
	}
}
*/
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*todel;

	if (!lst || !del)
		return ;
	todel = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		ft_lstdelone(todel, del);
		todel = *lst;
	}
}

/*
int main()
{
	t_list	*lst = NULL;
	ft_lstadd_back(&lst,ft_lstnew(ft_strdup("1")));
	ft_lstadd_back(&lst,ft_lstnew(ft_strdup("2")));
	ft_lstadd_back(&lst,ft_lstnew(ft_strdup("3")));

	ft_putlst(lst);
	ft_lstclear(&lst,free);
	printf("%p",lst);

*/
