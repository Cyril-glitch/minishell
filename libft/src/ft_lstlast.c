/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cycolonn <cycolonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:02:56 by cycolonn          #+#    #+#             */
/*   Updated: 2025/12/31 11:54:21 by cycolonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}
/*
   int main()
   {
   t_list  *lst = NULL;
   ft_lstadd_front(&lst,ft_lstnew("3"));
   ft_lstadd_front(&lst,ft_lstnew("2"));
   ft_lstadd_front(&lst,ft_lstnew("1"));
   t_list  *res = ft_lstlast(lst);

   printf("last node locate at : %p content : %s\n",res,(char*)res->content);
   }
 */
