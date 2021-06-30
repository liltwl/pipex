/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 17:38:46 by otaouil           #+#    #+#             */
/*   Updated: 2021/06/30 10:50:05 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <libgen.h>
# include <curses.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

char	**ft_free_split(char **d);
char	*ft_strjoin(char const *s1, char const *s2);
int		number_of_words(char *str, char c);
int		word_size(char *str, char c);
void	fill_string(char *str, char *cas, char c);
char	**ft_split(char const *s, char c);
int		ft_close(char *p, int i);
char	*ft_getabspath(char **path, char **tmp);
char	*ft_getpath(char **env, char *cmd);
void	exec_cmd(char *cmd1, char **env);
void	execpipe2(char *argv2, int *fds, char **env);
void	execpipe1(char *argv1, int *fds, char **env);
int		execpipe(char *argv1, char *argv2, char **env);
int		ft_getfd1(char *str);
int		ft_getfd2(char *str);
void	ft_pars(char **str);

#endif