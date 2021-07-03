#include "pipex.h"


char	*ft_mystrjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = strlen((char *)s1);
	j = strlen((char *)s2);
	if (!(p = malloc(i + j + 2)))
		return (0);
	strcpy(p, (char *)s1);
	strcpy(&p[i], "/");
	strcpy(&p[i + 1], (char *)s2);
	return (p);
}

int		number_of_words(char *str, char c)
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
	tab = (char**)malloc((n + 1) * 8);
	n = 0;
	while (s[++i] != '\0')
		if (s[i] != c)
		{
			if (n != 1)
			{
				if (!(tab[++j] = malloc(word_size((char *)&s[i], c) + 1)))
					return (NULL);
				fill_string((char *)&s[i], tab[j], c);
				n = 1;
			}
		}
		else
			n = 0;
	tab[++j] = 0;
	return (tab);
}

char				**ft_free_split(char **d)
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

int    ft_close(char *p, int i)
{
    write(2,p, strlen(p));
	write(2,"\n", 1);
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
		if((fd = open(cmd,O_RDONLY)) > 0)
			break ;
		close(fd);
		free(cmd);
	}
	close(fd);
	return (cmd);
}

char *ft_getpath(char **env, char *cmd)
{
	char **tmp;
	char **path;
	int	i;

	i = -1;
	tmp = ft_split(cmd, ' ');
	while (env[++i])
		if (!strncmp(env[i],"PATH",4))
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
    char    *pcmd;
    char    **cmd;
	
	cmd = ft_split(cmd1, ' ');
	pcmd = ft_getpath(env, cmd1);
	execve(pcmd, cmd, NULL);
	if (cmd)
		ft_free_split(cmd);
	ft_close("error : command not found", 127);
}

void    execpipe2(char *argv2, int *fds, char **env)
{
    close(fds[1]);
    dup2(fds[0], 0);
    close(fds[0]);
    exec_cmd(argv2, env);
}

void    execpipe1(char *argv1, int *fds, char **env)
{
    close(fds[0]);
    dup2(fds[1], 1);
    close(fds[1]);
    exec_cmd(argv1, env);
}

int execpipe(char *argv1, char *argv2, char **env)
{
    int fds[2];
    pid_t pid;
    pid_t pid1;
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

int execmlpipe(char **argv1, int i, char **env)
{
    int fds[2];
    pid_t pid;
	int		x;
	int		fd;

	fd = 0;
	x = -1;
	while (++x < i)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			ft_close("error : fork failed", 1);
		if (pid == 0)
		{
			if (x != 0)
			{
				dup2(fd, 0);
				close(fd);
			}
			if (i - 1 != x)
				dup2(fds[1], 1);
			close(fds[0]);
			exec_cmd(argv1[x], env);
		}
		else
		{
			wait(NULL);
			close(fds[1]);
			fd = fds[0];
		}
	}
    return (0);
}

int     ft_getfd1(char *str)
{
    int fd;

    if ((fd = open(str, O_RDONLY)) == -1)
        return 0;
    dup2(fd, 0);
	close(fd);
    return (1);
}

int     ft_getfd2(char *str)
{
    int fd;

    if ((fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1)
        return 0;
    dup2(fd, 1);
	close(fd);
    return (1);
}

int     ft_getfd3(char *str)
{
    int fd;
	
    if ((fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0666)) == -1)
        return 0;
    dup2(fd, 1);
	close(fd);
    return (1);
}

int     ft_getfd4(char *str)
{
    int fd[2];
	char	*line;
	int		x;

	x = 1;
	pipe(fd);
	while (x)
	{
		get_next_line(0, &line);
		x = strcmp(line, str);
		if (!x)
			break;
		else
			write(fd[1], line, strlen(line));
		free(line);
		write(fd[1], "\n", 1);
	}
	if (line)
		free(line);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);;
    return (1);
}

void    ft_pars(char **str, int y, int x, int z)
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

int main(int av,char **ac,char **env)
{
    if (av < 5)
    	ft_close("error : Invalid arguments", 1);
	if (!strcmp(ac[1], "here_doc"))
	{
    	ft_pars(ac, 2, av - 1, 1);
		execmlpipe(&ac[3], av - 4, env);
	}
	else if (av >= 5)
	{
		ft_pars(ac, 1, av - 1, 0);
		execmlpipe(&ac[2], av - 3, env);
	}
	else
		ft_pars(ac, 1, 4, 0);
	if (!ac[2][0] || !ac[3][0])
		ft_close("error : Invalid arguments", 1);
	//execpipe(ac[2], ac[3],env);
    return (0);
}