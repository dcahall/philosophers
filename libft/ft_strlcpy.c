/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:43:02 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 17:43:03 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	char	*d;
	char	*s;

	d = dst;
	s = (char *)src;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dstsize-- > 1 && *s)
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (ft_strlen(src));
}

// int main()
// {
// 	char src[11] = "0123456789";
// 	char dst[11] = "1111111111";
// 	printf("%lu\n", strlcpy(dst, src, 10));
// 	printf("%s", dst);
// }
