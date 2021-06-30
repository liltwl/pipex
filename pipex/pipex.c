/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:06:37 by otaouil           #+#    #+#             */
/*   Updated: 2021/06/30 10:18:01 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execpipe(char *argv1, char *argv2, char **env)
{
	int		fds[2];
	pid_t	pid;
	pid_t	pid1;
	int		x;

	x = 0;
	pid = fork();
	if (pid == -1)
		ft_close("error : fork failed", 1);
	if (pid == 0)
	{
		pipe(fds);
		pid1 = fork();
		if (pid1 == -1)
			ft_close("error : fork failed", 1);
		else if (pid1 > 0)
			execpipe1(argv1, fds, env);
		else
			execpipe2(argv2, fds, env);
	}
	else
		waitpid(pid, &x, 0);
	if (x == 0)
		return (0);
	return (127);
}

int	ft_getfd1(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_getfd2(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

void	ft_pars(char **str)
{
	if (ft_getfd1(str[1]) == 0)
		ft_close("error : no such file or directory", 0);
	if (ft_getfd2(str[4]) == 0)
		ft_close("error : no such file or directory", 0);
}

int	main(int av, char **ac, char **env)
{
	if (av != 5)
		ft_close("error : Invalid arguments", 1);
	if (!ac[2][0] || !ac[3][0])
		ft_close("error : Invalid arguments", 1);
	ft_pars(ac);
	return (execpipe(ac[2], ac[3], env));
}
