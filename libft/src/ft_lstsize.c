/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathis <mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:55:15 by cycolonn          #+#    #+#             */
/*   Updated: 2026/02/26 09:23:35 by mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*
   int main()
   {
   t_list  *lst = NULL;
   ft_lstadd_front(&lst,ft_lstnew("1"));
   ft_lstadd_front(&lst,ft_lstnew("2"));
   ft_lstadd_front(&lst,ft_lstnew("3"));

   printf("%d\n",ft_lstsize(lst));
   }
 */
