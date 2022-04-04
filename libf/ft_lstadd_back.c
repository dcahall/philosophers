/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:18:16 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 13:18:19 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)-> next = new;
}

// int main()
// {
// 	t_list *begin;
// 	t_list	el1;
// 	t_list	el2;
// 	t_list	el3;
// 	begin = &el1;
// 	el1.next = &el2;
// 	el2.next = &el3;
// 	el3.next = NULL;
// 	printf("%d\n", ft_lstsize(begin));
// 	ft_lstadd_back(begin)
// 	printf("%d\n", ft_lstsize(begin));
// }