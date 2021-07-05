/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:03:49 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/05 16:13:06 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	**ft_free_split(char **d)
{
	int	i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

int	ft_close(char *p, int i)
{
	write(2, p, strlen(p));
	write(2, "\n", 1);
	exit(i);
}
