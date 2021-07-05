/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 16:06:38 by otaouil           #+#    #+#             */
/*   Updated: 2021/07/05 17:10:17 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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

char	*ft_getabspath(char **path, char **tmp)
{
	int		i;
	char	*cmd;
	int		fd;

	i = -1;
	cmd = NULL;
	while (path[++i])
	{
		cmd = ft_mystrjoin(path[i], tmp[0]);
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
	ft_close("error : command not found", 127);
}
