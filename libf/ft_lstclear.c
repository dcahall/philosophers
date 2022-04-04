/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:56:26 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/21 14:56:30 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*delet;

	delet = *lst;
	if (!lst || !del)
		return ;
	while (delet != NULL)
	{
		delet = delet -> next;
		(*del)((*lst)-> content);
		free ((*lst));
		*lst = delet;
	}
	*lst = NULL;
}
