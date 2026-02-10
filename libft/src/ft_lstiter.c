/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:45:15 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
/*
void	ft_setzero(void	*content)
{
	*(unsigned char *)content = '0';
}

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

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		f(tmp->content);
		tmp = tmp->next;
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
	printf("\n");
	ft_lstiter(lst,ft_setzero);
	ft_putlst(lst);
}
*/
