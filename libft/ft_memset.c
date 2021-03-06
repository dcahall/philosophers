/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 18:10:11 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 18:10:13 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len--)
		str[len] = (unsigned char)c;
	return (b);
}

// int main ()
// {
// 	char	str[11] = "";
// 	printf("%s", ft_memset(str, 'k', 10));
// }