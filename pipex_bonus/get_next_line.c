/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 01:28:05 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/03 15:51:18 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_mychr(const char *s, int c)
{
	while (*(char*)s != '\0' && *s != (char)c)
		s++;
	return ((char*)s);
}

char	*ft_strdup(const char *src)
{
	char *res;

	if (!(res = (char *)malloc(ft_strlen((char *)src) + 1)))
		return (0);
	ft_strcpy(res, (char *)src);
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	if (!(p = malloc(i + j + 1)))
		return (0);
	ft_strcpy(p, (char *)s1);
	ft_strcpy(&p[i], (char *)s2);
	return (p);
}

size_t	ft_strlcpy(char *d, const char *s, size_t n)
{
	size_t		k;
	void		*dest;

	dest = d;
	k = ft_strlen(s);
	if (n == 0)
		return (k);
	if (dest == NULL)
		return (0);
	if (n)
	{
		while (n - 1 > 0 && *s)
		{
			*(unsigned char *)dest++ = *(unsigned char *)s++;
			n--;
		}
	}
	*(unsigned char *)dest = '\0';
	return (k);
}

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
