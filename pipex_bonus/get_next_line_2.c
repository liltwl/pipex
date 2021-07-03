/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:54:43 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/03 15:51:24 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int i;

	i = -1;
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	while (*(char*)s != '\0' && *s != (char)c)
		s++;
	if (*(char*)s == (char)c)
		return ((char*)s);
	return (0);
}

char	*ft_myft(char *p, char *cd, char *bf, int i)
{
	bf[i] = '\0';
	p = cd;
	cd = ft_strjoin(cd, bf);
	free(p);
	return (cd);
}

char	*ft_free(char *p, char *bf, char *cd, int i)
{
	if (*ft_mychr(cd, '\n') != '\0')
		cd = ft_strdup(ft_mychr(cd, '\n') + 1);
	else
		cd = ft_strdup(ft_mychr(cd, '\n'));
	free(p);
	free(bf);
	if (i != 1)
	{
		p = cd;
		cd = 0;
		free(p);
		return (0);
	}
	return (cd);
}

int		get_next_line(int fd, char **line)
{
	char		*p;
	char		*bf;
	static char	*cd[1024];
	int			i;

	p = NULL;
	bf = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || !line || BUFFER_SIZE < 0)
		return (-1);
	if (!cd[fd])
		cd[fd] = ft_strdup("\0");
	*line = ft_strdup("\0");
	while (!ft_strchr(cd[fd], '\n') && (i = read(fd, bf, BUFFER_SIZE)) > 0)
		cd[fd] = ft_myft(p, cd[fd], bf, i);
	free(bf);
	bf = *line;
	if (i == -1 || !*(p = cd[fd]))
		return (i == -1 ? -1 : 0);
	if (ft_strchr(cd[fd], '\n'))
		i = 1;
	*line = malloc(((size_t)(ft_mychr(cd[fd], '\n') - cd[fd]) + 1));
	ft_strlcpy(*line, cd[fd], (size_t)(ft_mychr(cd[fd], '\n') - cd[fd] + 1));
	cd[fd] = ft_free(p, bf, cd[fd], i);
	return (i == 1 ? 1 : 0);
}
