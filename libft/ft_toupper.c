/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toupper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:49:38 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 17:49:41 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <ctype.h>
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}

// int main ()
// {
// 	printf("%c", ft_toupper('z'));
// }
