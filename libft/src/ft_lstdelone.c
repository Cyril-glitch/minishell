/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:40:04 by cycolonn          #+#    #+#             */
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

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del (lst->content);
	free(lst);
}

/*
int	main()
{
	t_list	*lst = NULL;
	ft_lstadd_back(&lst,ft_lstnew(strdup("1")));
	ft_lstadd_back(&lst,ft_lstnew(strdup("2")));
	ft_lstadd_back(&lst,ft_lstnew(strdup("3")));


	ft_putlst(lst);
	ft_lstdelone(lst->next->next,free);
	ft_lstdelone(lst->next,free);
	ft_lstdelone(lst,free);

}
*/
