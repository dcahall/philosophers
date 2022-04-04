/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 17:42:32 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/11 17:42:35 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if ((unsigned char *)src >= (unsigned char *)dst)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len--)
			d[len] = s[len];
		return (dst);
	}
}

// int main()
// {
// 	unsigned char src[11] = "0123456789";

// 	//ft_memmove(&src[1], &src[2], 3);
// 	memmove(&src[1], &src[2], 3);
// 	printf("%s", src);
// }
