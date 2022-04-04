/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:41:46 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 17:41:48 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// int main()
// {
//     printf("%zu\n", ft_strlen("1"));
//     printf("%lu", strlen("1"));
// }
