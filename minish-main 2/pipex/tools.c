#include "pipex.h"

int		word_size(char *str, char c)
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
	n = number_of_words((char *)s, c);
	tab = (char **)malloc((n + 1) * 8);
	n = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			if (n != 1)
			{
				tab[++j] = malloc(word_size((char *)&s[i], c) + 1);
				if (!(tab[++j]))
					return (NULL);
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

char	**ft_free_split(char **d)
{
	int				i;

	i = 0;
	while (d[i])
	{
		free(d[i]);
		i++;
	}
	free(d);
	return (NULL);
}

void	ft_close(char *p)
{
	perror(p);
	exit(EXIT_FAILURE);
}
