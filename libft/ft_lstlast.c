/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 12:51:51 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 12:51:53 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*check;

	check = lst;
	if (!lst)
		return (NULL);
	while (check)
	{
		if (check -> next == NULL)
			return (check);
		check = check -> next;
	}
	return (NULL);
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
// 	el3.content = "123";
// 	printf("%s\n", el3.content);
// 	printf("%s", ft_lstlast(begin) -> content);
// }