/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 01:28:05 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/05 17:00:44 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char p)
{
	char	*tmp;
	int		i;

	i = ft_strlen(str);
	tmp = malloc(i + 2);
	i = -1;
	while (str && str[++i])
		tmp[i] = str[i];
	tmp[i++] = p;
	tmp[i] = '\0';
	if (str)
		free (str);
	return (tmp);
}

int	get_next_line(int fd, char **line)
{
	int		i;
	char	buff[1];
	char	*str;

	str = malloc(1);
	str[0] = '\0';
	i = read(fd, buff, 1);
	while (i && buff[0] != '\n')
	{
		str = ft_strjoin(str, buff[0]);
		i = read(fd, buff, 1);
	}
	*line = str;
	if (buff[0] == '\n')
		i = 1;
	else
		i = 0;
	return (i);
}
