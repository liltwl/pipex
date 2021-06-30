/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:02:35 by otaouil           #+#    #+#             */
/*   Updated: 2021/06/30 10:35:40 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = strlen((char *)s1);
	j = strlen((char *)s2);
	p = malloc(i + j + 2);
	if (!(p))
		return (0);
	strcpy(p, (char *)s1);
	strcpy(&p[i], "/");
	strcpy(&p[i + 1], (char *)s2);
	return (p);
}

int	number_of_words(char *str, char c)
{
	int	nbr;
	int	i;
	int	indice;

	nbr = 0;
	i = 0;
	indice = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			if (indice != 1)
			{
				nbr++;
				indice = 1;
			}
		}
		else
			indice = 0;
		i++;
	}
	return (nbr);
}

int	word_size(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

void	fill_string(char *str, char *cas, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
	{
		cas[i] = str[i];
		i++;
	}
	cas[i] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		n;
	int		i;
	int		j;

	i = -1;
	j = -1;
	tab = (char **)malloc((number_of_words((char *)s, c) + 1) * 8);
	n = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			if (n != 1)
			{
				tab[++j] = malloc(word_size((char *)&s[i], c) + 1);
				fill_string((char *)&s[i], tab[j], c);
				n = 1;
			}
		}
		else
			n = 0;
	}
	tab[++j] = 0;
	return (tab);
}
