/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:29:46 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/10 15:29:49 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	pointer = NULL;
	pointer = malloc(count * size);
	if (pointer == NULL)
		return (NULL);
	ft_bzero(pointer, count * size);
	return (pointer);
}

// int main()
// {
// 	int i = 0;
// 	char *str;
// 	str = (char *) ft_calloc(5, sizeof(char));
// 	while (i < 5)
// 	{
// 		str[i] = '9';
// 		i++;
// 	}
// 	printf("%s", str);
// }
