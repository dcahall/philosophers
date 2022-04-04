/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:32:19 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 12:32:22 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*counter;
	int		size_list;

	size_list = 0;
	counter = lst;
	while (counter)
	{
		counter = counter -> next;
		size_list++;
	}
	return (size_list);
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
// 	printf("%d", ft_lstsize(begin));
// }