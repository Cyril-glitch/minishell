/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:51:42 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../inc/libft.h"

/*
   void  ft_putlst(t_list  *lst)
   {
   t_list  *current = lst;
   while(current)
   {
   printf("%d",*(int*)current->content);
   current = current->next;
   }
   }
 */

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
	{
		new->next = *lst;
		*lst = new;
	}
	else
		*lst = new;
}

/*
   int main  ()
   {
   int a = 1;
   int b = 2;
   int c = 3;
   int d = 0;
//int e = -1;

t_list *lst  = ft_lstnew(&a);
lst->next = ft_lstnew(&b);
lst->next->next = ft_lstnew(&c);

ft_lstadd_front(&lst,ft_lstnew(&d));

ft_putlst(lst);

return 0;
}
 */
