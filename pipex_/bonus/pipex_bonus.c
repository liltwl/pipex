/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:07:58 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/05 16:07:58 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	ft_getfd4(char *str)
{
	int		fd[2];
	char	*line;
	int		x;

	x = 1;
	pipe(fd);
	while (x)
	{
		get_next_line(0, &line);
		x = strcmp(line, str);
		if (!x)
			break ;
		else
			write(fd[1], line, strlen(line));
		free(line);
		write(fd[1], "\n", 1);
	}
	if (line)
		free(line);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	return (1);
}

void	ft_pars(char **str, int y, int x, int z)
{
	if (z == 0 && ft_getfd1(str[y]) == 0)
		ft_close("error : no such file or directory", 0);
	if (z == 0 && ft_getfd2(str[x]) == 0 && z == 0)
		ft_close("error : no such file or directory", 0);
	if (z == 1)
	{
		if (ft_getfd3(str[x]) == 0)
			ft_close("error : no such file or directory", 0);
		ft_getfd4(str[y]);
	}
}

int	main(int av, char **ac, char **env)
{
	if (av < 5)
		ft_close("error : Invalid arguments", 1);
	if (!ac[2][0] || !ac[3][0])
		ft_close("error : Invalid arguments", 1);
	if (!strcmp(ac[1], "here_doc"))
	{
		ft_pars(ac, 2, av - 1, 1);
		return (execmlpipe(&ac[3], av - 4, env));
	}
	else if (av >= 5)
	{
		ft_pars(ac, 1, av - 1, 0);
		return (execmlpipe(&ac[2], av - 3, env));
	}
	return (0);
}
