/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 10:05:00 by otaouil           #+#    #+#             */
/*   Updated: 2021/06/30 11:07:21 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_getabspath(char **path, char **tmp)
{
	int		i;
	char	*cmd;
	int		fd;

	i = -1;
	cmd = NULL;
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], tmp[0]);
		fd = open(cmd, O_RDONLY);
		if (fd > 0)
			break ;
		close(fd);
		free(cmd);
	}
	close(fd);
	return (cmd);
}

char	*ft_getpath(char **env, char *cmd)
{
	char	**tmp;
	char	**path;
	int		i;

	i = -1;
	tmp = ft_split(cmd, ' ');
	while (env[++i])
		if (!strncmp(env[i], "PATH", 4))
			cmd = *(env + i) + 5;
	path = ft_split(cmd, ':');
	if (!tmp[0])
		return (NULL);
	cmd = ft_getabspath(path, tmp);
	ft_free_split(path);
	ft_free_split(tmp);
	return (cmd);
}

void	exec_cmd(char *cmd1, char **env)
{
	char	*pcmd;
	char	**cmd;

	cmd = ft_split(cmd1, ' ');
	pcmd = ft_getpath(env, cmd1);
	execve(pcmd, cmd, NULL);
	if (cmd)
		ft_free_split(cmd);
	ft_close("er   127);
}

void	execpipe2(char *argv2, int *fds, char **env)
{
	close(fds[1]);
	dup2(fds[0], 0);
	close(fds[0]);
	exec_cmd(argv2, env);
}

void	execpipe1(char *argv1, int *fds, char **env)
{
	close(fds[0]);
	dup2(fds[1], 1);
	close(fds[1]);
	exec_cmd(argv1, env);
}
