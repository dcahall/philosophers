/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcahall <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:36:22 by dcahall           #+#    #+#             */
/*   Updated: 2021/10/14 19:36:24 by dcahall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		substr = (char *) malloc(sizeof(char) * (ft_strlen(s + start) + 1));
	else
		substr = (char *) malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (s[i + start] && len--)
		{
			substr[i] = s[i + start];
			i++;
		}
	}
	substr[i] = '\0';
	return (substr);
}

// int main()
// {
// 	printf("%s", ft_substr("lorem ipsum dolor sit amet", 0, 10));
// }
